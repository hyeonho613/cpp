#include <stdio.h>

// int main()
// {
// 	int height;

// 	printf("높이를 입력하세요 : ");
// 	scanf("%d", &height);
// 	for (int i = 1; i <= height; i++)
// 	{
// 		for (int j = 0; j<height - i; j++) 
// 			printf("OOO");
// 		for (int j = 0; j<i; j++)
// 			printf("%3d", j * 2 + 1);
// 		for (int j = i - 2; j >= 0; j--)
// 			printf("%3d", j * 2 + 1);
// 		printf("\n");
// 	}
// }


int main()
{
	int height;

	printf("높이를 입력하세요 : ");
	scanf("%d", &height);
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j<=height - i; j++) 
			printf("OOO");
		for (int j = 1; j<=i; j++)
			printf("%3d", j * 2 - 1);
		for (int j = i - 1; j >= 1; j--)
			printf("%3d", j * 2 - 1);
		printf("\n");
	}
}