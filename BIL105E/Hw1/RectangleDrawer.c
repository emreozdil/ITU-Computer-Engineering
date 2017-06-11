//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <stdio.h>

int main()
{
	int choice, height, width, thickness, new_thickness, i, j;
	do
	{
		printf("Enter the height for your rectangle: ");
		scanf("%d",&height);
		printf("Enter the width for your rectangle: ");
		scanf("%d",&width);
		printf("Enter the thickness: ");
		scanf("%d",&thickness);
		if(height<=2*thickness && width<=2*thickness)
		{
			printf("It is not possible to draw your rectangle with the specified thickness. The rectangle without the thickness option is drawn below:\n");
			for (i = 0; i <height ; i++)
			{
				for (j = 0; j < width; j++)
				{
					printf("*");
				}
				printf("\n");
			}				
		}
		else if (height>2*thickness && width<=2*thickness)
		{
			new_thickness=thickness;
			for (i = 0; i < thickness; i++)
			{
				for (j = 0; j < width; j++)
				{
					printf("*");
				}
			printf("\n");
			}
			while(new_thickness--)
			{
				if (width>2*new_thickness)
				{
					for (i = 0; i <(height-2*thickness) ; i++)
					{
						for (j = 0; j < new_thickness; j++)
						{
							printf("*");
						}
						for (j = 0; j <(width-2*new_thickness); j++)
						{
							printf(" ");
						}
						for (j = 0; j <new_thickness; j++)
						{
							printf("*");
						}
						printf("\n");
					}
				break;
				}
				else
					continue;					
			}
			for (i = 0; i < thickness; i++)
			{
				for (j = 0; j < width; j++)
				{
					printf("*");
				}
				printf("\n");
			}
		}	
		else if (height<=2*thickness && width>2*thickness)
		{
			new_thickness=thickness;
			while (new_thickness--)
			{
				if(height>2*new_thickness)
				{
					for (i = 0; i <new_thickness; i++)
					{
						for (j = 0; j < width; j++)
						{
							printf("*");
						}
						printf("\n");
					}
					for (i = 0; i < height-2*new_thickness; i++)
					{
						for (j = 0; j <thickness ; j++)
						{
							printf("*");
						}
						for (j = 0; j <width-2*thickness ; j++)
						{
							printf(" ");
						}
						for (j = 0; j <thickness ; j++)
						{
							printf("*");
						}
						printf("\n");
					}
					for (i = 0; i <new_thickness; i++)
					{
						for (j = 0; j < width; j++)
						{
							printf("*");
						}
						printf("\n");
					}
					break;
				}
				else
					continue;
			}			
		}
		else
		{
			for (i = 0; i < thickness; i++)
			{
				for (j = 0; j < width; j++)
				{
					printf("*");
				}
				printf("\n");
			}
			for (i = 0; i <(height-2*thickness) ; i++)
			{
				for (j = 0; j < thickness; j++)
				{
					printf("*");
				}
					for (j = 0; j <(width-2*thickness); j++)
				{
					printf(" ");
				}
				for (j = 0; j < thickness; j++)
				{
					printf("*");
				}
				printf("\n");
			}
			
			for (i = 0; i < thickness; i++)
			{
				for (j = 0; j < width; j++)
				{
					printf("*");
				}
				printf("\n");
			}
		}
		printf("Do you want to continue?(1 for Yes, 0 for No): ");
		scanf("%d", &choice);
		if(choice==0)
			break;			
	}
	while(choice==1);
	return 0;
}
