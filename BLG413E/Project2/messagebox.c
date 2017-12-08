#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>
#include <linux/file.h> 
#include <linux/cred.h> 
#include <linux/uidgid.h>
#include <linux/sched.h>

#include <asm/switch_to.h>		/* cli(), *_flags */
#include <asm/uaccess.h>	/* copy_*_user */

#include "messagebox.h"

#define MESSAGEBOX_MAJOR 0
#define MESSAGEBOX_NR_DEV 1
#define MESSAGEBOX_CAPACITY 5

int messagebox_major = MESSAGEBOX_MAJOR;
int messagebox_minor = 0;
int messagebox_nr_dev = MESSAGEBOX_NR_DEV;
int messagebox_capacity = MESSAGEBOX_CAPACITY;

module_param(messagebox_major, int, S_IRUGO);
module_param(messagebox_minor, int, S_IRUGO);
module_param(messagebox_nr_dev, int, S_IRUGO);
module_param(messagebox_capacity, int, S_IRUGO);

MODULE_AUTHOR("Emre ÖZDIL, Merve ECEVIT");
MODULE_LICENSE("Dual BSD/GPL");

struct message {
	char *text;
	int isRead;
	char *fromUsername;
	int messageSize;
	struct message* next;
};	

struct account {
	char *username;
	struct message* receivedMessages;
	int unreadCount;
	int totalMessage;
	struct account* next;
};

struct messagebox_dev {
	struct account* users;
	int isInclude;
    struct semaphore sem;
    struct cdev cdev;
};

struct messagebox_dev *messagebox_device;


int messagebox_trim(struct messagebox_dev *dev){
	
	printk(KERN_INFO "Messagebox: Trim function\n");
	struct account* tempUser;
	struct message* tempMessage;
	
	while(messagebox_device->users != NULL) {
		tempUser = messagebox_device->users;
		while(tempUser->receivedMessages != NULL) {
			tempMessage = tempUser->receivedMessages;
			tempUser->receivedMessages = tempUser->receivedMessages->next;
			kfree(tempMessage->text);
			kfree(tempMessage);
		}
		messagebox_device->users = messagebox_device->users->next;
		kfree(tempUser->receivedMessages);
		kfree(tempUser);
	}
    return 0;
}

int messagebox_open(struct inode *inode, struct file *filp){
	printk(KERN_INFO "Messagebox: Open function\n");
    struct messagebox_dev *dev;

    dev = container_of(inode->i_cdev, struct messagebox_dev, cdev);
    filp->private_data = dev;
    printk(KERN_INFO "Messagebox: Open function mode %d\n", dev->isInclude);
	
    return 0;
}


int messagebox_release(struct inode *inode, struct file *filp){
	printk(KERN_INFO "Messagebox: Release function\n");
    return 0;
}

char* getUsername(uid_t id){
	char* kernelUsername = kmalloc(10, GFP_KERNEL);
	char* kernelUserId = kmalloc(5, GFP_KERNEL);
	char __user *username = (__force char __user *)kernelUsername;
	char __user *userId = (__force char __user *)kernelUserId;	
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);
	char buf[1];

	struct file *passwdFile = filp_open("/etc/passwd",O_RDONLY, 0);
	if (IS_ERR(passwdFile)) {
		printk(KERN_INFO "open /etc/passwd for getuid error\n");
		return;
	}
	
	char firstDelimiter = ':';
	char secondDelimiter = '\n';
	passwdFile->f_pos = 0;
	int index;
	int i;
	int textSize = 100;
	while(textSize--) {
		i = 0;
		index = 0;
		vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		//printk(KERN_INFO "ilk: %c\n", buf[0]);
		while(buf[0] != firstDelimiter)
		{
			username[i] = buf[0];
			i++;
			vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		}
		username[i] = '\0';
		vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		
		i = 0;
		while(buf[0] != firstDelimiter)
		{
			userId[i] = buf[0];
			i++;
			vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		}
		userId[i] = '\0';
		uid_t uid = 0;
		char temp = userId[index];
		while(temp != '\0') {
			//printk(KERN_INFO "iiiii: %d \n", i);
			//printk(KERN_INFO "ii: %c \n", temp);
			uid *= 10;
			uid += (temp-'0');
			index++;
			temp = userId[index];
		}
		printk(KERN_INFO "uid: %d id %d \n", uid, id);
		if(uid == id) {
			return username;
		}
		vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		while(buf[0] != secondDelimiter)
		{
			//printk(KERN_INFO "buf: %c \n", buf[0]);
			vfs_read(passwdFile, buf, 1, &passwdFile->f_pos);
		}
		//printk(KERN_INFO "son: %c\n", buf[0]);
	}	
}



ssize_t messagebox_read(struct file *filp, char __user *buf, size_t count,
                   loff_t *f_pos)
{
	printk(KERN_INFO "Messagebox: Read function\n");
	
    struct messagebox_dev *dev = filp->private_data;
    ssize_t retval = 0;
    int i, j, size = 0;
	loff_t position = *f_pos;
	struct message* tempMessage;
	
	kuid_t id = get_current_user()->uid;
	char *username=kmalloc(15, GFP_KERNEL);
	username = getUsername(id.val);
    
	if (dev->isInclude) {
		(*f_pos)++;
	}
    
    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
	
	if(dev->users == NULL){
		printk(KERN_INFO "Messagebox: No such a user\n");
		retval = 0;
		goto out;
	}
	else{
		printk(KERN_INFO "Messagebox: Else\n");
		struct account *traverseAccount = dev->users;
		while (traverseAccount != NULL){
			printk(KERN_INFO "Messagebox: %s%s\n", traverseAccount->username, username );
			if(strcmp(traverseAccount->username, username)==0){
				if (traverseAccount->receivedMessages == NULL) {
					retval = 0;
					goto out;
				}
				else {
					tempMessage = traverseAccount->receivedMessages;
					while (tempMessage != NULL) {
						if(dev->isInclude || !tempMessage->isRead){
							if (position > 0) {
								position--;
								tempMessage = tempMessage->next;
								continue;
							}
							if (copy_to_user(buf, tempMessage->text, tempMessage->messageSize)) {
								retval = -EFAULT;
								goto out;
							}
							size = tempMessage->messageSize;
							tempMessage->isRead = 1;
							traverseAccount->unreadCount--;
							tempMessage = tempMessage->next;
							goto changeRetval;
						}
						else {
							tempMessage = tempMessage->next;
						}
					}
				}
			}
			traverseAccount = traverseAccount->next;
		}
	}
	changeRetval:
	retval = size;
	if (position > 0){
		 retval = 0;
	}
		
	out:
	up(&dev->sem);
	return retval;
}


ssize_t messagebox_write(struct file *filp, const char __user *buf, size_t count,
                    loff_t *f_pos)
{
	printk(KERN_INFO "Messagebox: Write function\n");
    struct messagebox_dev *dev = filp->private_data;
    ssize_t retval = -ENOMEM;
   
    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;

	char firstDelimiter = ' ';
	int i = 1;
	
	while(buf[i] != firstDelimiter)
	{
		i++;
	}
	int toLength = i-1;
	printk(KERN_INFO "toLength: %d \n", toLength);
	int j;
	char* to = kmalloc(toLength + 1, GFP_KERNEL);
	for(j = 0; j < toLength; j++) {
		to[j] = buf[j + 1];
	}
	to[toLength] = '\0';
	printk(KERN_INFO "to: %s \n", to);
	int msgLength = count - toLength - 1;
	printk(KERN_INFO "msgLength: %d %d \n", msgLength, i);
	int k;
	char* msg = kmalloc(msgLength + 1, GFP_KERNEL);
	char* msgWithName = kmalloc(msgLength+toLength+1, GFP_KERNEL);
	for(k = 0; k < msgLength; k++) {
		msg[k] = buf[k + i + 1];
	}
	msg[msgLength] = '\0';
    printk(KERN_INFO "msg: %s \n", msg);
    kuid_t id = get_current_user()->uid;
	printk(KERN_INFO "id.val: %d \n", id.val);
	char *username=kmalloc(15, GFP_KERNEL);
	username = getUsername(id.val);
	//username = getUsername(2);
	printk(KERN_INFO "username: %s \n", username);
    for(k = 0; k < msgLength+toLength+1; k++) {
		if (k < toLength + 1)
			msgWithName[k] = username[k];
		else if (k == toLength + 1)
			msgWithName[k] = ':';
		else
			msgWithName[k] = msg[k-toLength-2];
	}
	msgWithName[k] = '\0';
	
    struct message *tempMessage;
    tempMessage = kmalloc(sizeof(struct message), GFP_KERNEL);
    
 
    tempMessage->text=msgWithName;
    tempMessage->fromUsername = username;
    tempMessage->isRead=0;
	tempMessage->messageSize = toLength+msgLength+2; 
    tempMessage->next = NULL;

    struct account *tempAccount;
    tempAccount = kmalloc(sizeof(struct account), GFP_KERNEL);
    tempAccount->username = to;
    tempAccount->receivedMessages = tempMessage;
    printk(KERN_INFO "messagebox: %s \n", tempAccount->receivedMessages->text);
    tempAccount->totalMessage = 0;
    tempAccount->unreadCount = 0;
    tempAccount->next = NULL;
    int isAdded=0;
	struct account *traverseAccount = dev->users;
	struct account *lastAccount;
	struct message *traverseMessage;
	 
	if(traverseAccount == NULL){
		dev->users = tempAccount;
		tempAccount->unreadCount++;
		printk(KERN_INFO "messagebox: First user is added %s\n");
	}
	else {
		while (traverseAccount != NULL){
			traverseMessage = traverseAccount->receivedMessages;
			printk(KERN_INFO "messagebox: strcmp: %s %s \n", traverseAccount->username, to);
			if(strcmp(traverseAccount->username, to)==0){
				if (traverseMessage == NULL) {
					traverseMessage = tempMessage;
					printk(KERN_INFO "11111111111messagebox: received null\n");
				}
				else {
					if(traverseAccount->unreadCount == messagebox_capacity){
						retval = -ENOMEM;
						goto out;
					}
					while (traverseMessage->next != NULL) {
						traverseMessage = traverseMessage->next;
					}
					traverseMessage->next = tempMessage;
				}
				traverseAccount->totalMessage++;
				traverseAccount->unreadCount++;
				isAdded=1;
				printk(KERN_INFO "messagebox: Message is added \n");
				goto changeRetval;
			}
			else {
				printk(KERN_INFO "messagebox: else \n");
				lastAccount = traverseAccount;
				traverseAccount = traverseAccount->next;
			}
		}
		if(!isAdded){
			printk(KERN_INFO "messagebox: ikinci user \n");
			traverseAccount = tempAccount;
			traverseAccount->totalMessage++;
			traverseAccount->unreadCount++;
			lastAccount->next = traverseAccount;
			printk(KERN_INFO "messagebox: User is added \n");
		}
	}
	changeRetval:
    retval = count;
    
  out:
    up(&dev->sem);
    return retval;
}

long messagebox_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	printk(KERN_INFO "Messagebox: Ioctl function\n");
	struct messagebox_dev *dev = filp->private_data;
	
	int err = 0;
	int retval = 0;
	
	//TODO HEPSINI SIL
	switch(cmd) {
		case MESSAGEBOX_SET_EXCLUDE_MODE:
			if (! capable (CAP_SYS_ADMIN)){
					return -EPERM;
				}
			dev->isInclude = 0;
			break;

		case MESSAGEBOX_SET_INCLUDE_MODE: /* Set: arg points to the value */
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			dev->isInclude = 1;
			printk(KERN_INFO "Messagebox: Ioctl include function mode %d\n", dev->isInclude);
			break;
			
		case MESSAGEBOX_DELETE_ALL_MESSAGES_MODE:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			char* username = kmalloc(16, GFP_KERNEL); 
			if (copy_from_user(username, arg, 16))
				return -EFAULT;
				printk(KERN_INFO "Messagebox not\n");
			// TODO get UserId
			int userId = 1;
			struct account *traverseAccount = dev->users;
			struct message *traverseMessage;
			struct message *tempMessage;
			int isFound = 0;
			while(traverseAccount){
				if(strcmp(traverseAccount->username, arg) == 0){
					isFound=1;
					traverseMessage = traverseAccount->receivedMessages->next;
					while(traverseMessage != NULL) {
						tempMessage = traverseMessage;
						traverseMessage = traverseMessage->next;
						kfree(tempMessage->text);
						kfree(tempMessage);
					}
					kfree(traverseAccount->receivedMessages->text);
					kfree(traverseAccount->receivedMessages);
					printk(KERN_INFO "222222222222222222 not found\n");
					break;
				}
				else {
					traverseAccount = traverseAccount->next;
				}
			}
			printk(KERN_INFO "Messagebox not found\n");
			if(!isFound){
				printk(KERN_INFO "Messagebox not found\n");
				return -EFAULT;
			}
			break;
		case MESSAGEBOX_MAX_UNREAD_MODE:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			messagebox_capacity = arg;
			break;

		default:  /* redundant, as cmd was checked against MAXNR */
			return -ENOTTY;
	}
	return retval;
}


loff_t messagebox_llseek(struct file *filp, loff_t off, int whence)
{
    return -EPERM;
}


struct file_operations messagebox_fops = {
    .owner =    THIS_MODULE,
    .llseek =   messagebox_llseek,
    .read =     messagebox_read,
    .write =    messagebox_write,
    .unlocked_ioctl =  messagebox_ioctl,
    .open =     messagebox_open,
    .release =  messagebox_release,
};


void messagebox_cleanup_module(void)
{
	printk(KERN_WARNING "Messagebox: Cleanup module \n");
    dev_t devno = MKDEV(messagebox_major, messagebox_minor);

    if (messagebox_device) {
		messagebox_trim(messagebox_device);
		cdev_del(&messagebox_device[0].cdev);
		kfree(messagebox_device);
	}
    unregister_chrdev_region(devno, 1);
    printk(KERN_WARNING "Messagebox: Cleanup finished \n");
}


int messagebox_init_module(void)
{
	printk(KERN_INFO "Messagebox: Init function\n");
    int result;
    int err;
    dev_t devno = 0;
    struct messagebox_dev *dev;

    if (messagebox_major) {
        devno = MKDEV(messagebox_major, messagebox_minor);
        result = register_chrdev_region(devno, messagebox_nr_dev, "messagebox");
    } else {
        result = alloc_chrdev_region(&devno, messagebox_minor, 1, "messagebox");
        messagebox_major = MAJOR(devno);
    }
    if (result < 0) {
        printk(KERN_WARNING "Messagebox: Can't get major %d\n", messagebox_major);
        return result;
    }
    
    printk(KERN_INFO "Messagebox: Major number %d\n", messagebox_major);

    messagebox_device = kmalloc(messagebox_nr_dev * sizeof(struct messagebox_dev), GFP_KERNEL);
    if (!messagebox_device) {
        result = -ENOMEM;
        goto fail;
    }
    memset(messagebox_device, 0, messagebox_nr_dev * sizeof(struct messagebox_dev));
	
    dev = messagebox_device;
	dev->isInclude = 0;
	sema_init(&dev->sem,1);
	cdev_init(&dev->cdev, &messagebox_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &messagebox_fops;
	
	err = cdev_add(&dev->cdev, devno, 1);
	
	if (err)
		printk(KERN_NOTICE "Error %d adding messagebox", err);

    return 0; /* succeed */

  fail:
	printk(KERN_ALERT "Messagebox: failed \n");
    messagebox_cleanup_module();
    return result;
}

module_init(messagebox_init_module);
module_exit(messagebox_cleanup_module);
