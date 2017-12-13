### Project 2 Repository:

[GitHub Link](https://github.com/cobang/HCoder-HServer)


BLG439 - Computer Project I - Project 2
========================================

Aim:
----

In this project, you are going to write an Android application (named HCoder) and a server (HServer) for the tranmission of compressed text files. Huffman coding will be used for compression.

Deadline:
---------

Nov 13, 2017, 13:00


Huffman coding:
---------------

You can find numerous tutorial about the details of Huffman coding. You should compute the symbol statistics (or probabilities) from the text that is required to be sent. This will require the transmission of the codebook along with the compressed text file.

Connection:
-----------

The connections can be peer to peer between 2 Android devices through a server (via HTTP) with a known IP.
When a user starts HCoder application, the application should ask for a username.
The application will register the username and other connection info to the server.

When a user wants to share a text file, the application will help user to select a text file within the device. Then the application will compress the text file using Huffman coding. Then, in order to send the compressed file, the user should select an active user that is registered at the server (or the server as the receiving end).

At the server side, when a file and receiving username arrives, it should warn the receiving user about the incoming file. When the receving user accepts, the compressed text file should be transferred to the receiving
user. The file should be decoded (uncompressed) at the receiver's Android device.

It should also be possible to compress textfile and send it to an active user from the server. In additon, a user should be able to choose the server as the receiving side. In this case, the file should be decoded at the server.

Usage of Libraries:
-------------------

You should not use any library for Huffman encoding/decoding, or bit manipulation. However, you can use libraries for communication.

Programming Language:
---------------------

Android devices should be programmed using Java. Server side can be implemented using any language such as PHP, Python etc.

Grading:
--------

The students will be responsible from different parts of the project.

Student 1:
Implementation of Huffman encoding (compression) of HCoder.
HCoder user interface for logging/file selection.

Student 2:
Implementation of Huffman decoding (compression) of HCoder.
HCoder communication with the HServer.

Student 3:
Implementation of Huffman encoding/decoding of HServer.
Other server functions that are described above.

Submissions:
------------

- report
- presentation
- documentation
- code link to a repository

Report should include the design criteria, used libraries, issues, implementation steps and the parts implemented by each member of the group. The report must be a single pdf document.

All submissions are done through Ninova system once per group.
