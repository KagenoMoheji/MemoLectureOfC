#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHARBUFF 124

int isIntArray(char*, char*);
int isDelimiter(char, char*);
 
int main(void){
	char input[CHARBUFF]; //�W�����͂��i�[����ϐ��D
	char delimiter[]=":, "; // �����ŋ�؂蕶�����w��D
	char *splitted_p; // strtok()�̖߂�l�ł���A�h���X���i�[����ϐ��D
	int elem_num, sum, ave; //������̌��C���v�l�C���ϒl

	while(1){
		elem_num=0, sum=0, ave=0;

		printf("Input numbers: ");
		//scanf("%s",input); //����ł͋󔒂�ǂݍ��߂Ȃ��I�I�󔒂�\0�ɂȂ肻���œ��͂̏I���ɂȂ��Ă��܂��i���̖͂��[�ɂ�\0�������ǋL�����j�D
		fgets(input,CHARBUFF,stdin); //�������Ȃ�󔒂�1�����Ƃ��ēǂݍ���ł����D�������Ō��\n������D������c��
		input[strlen(input)-1]='\0'; //�Ō�̕�����\n����\0�ɒu������D

		// Quit���ǂ����B
		if(!strcmp(input,"Q")){
			printf("Bye\n");
			break;
		}

		// �����E�w��̋�؂蕶���ȊO���܂܂�Ă��Ȃ����ǂ����D
		if(!isIntArray(input,delimiter)){
			printf("IOERROR: Input only numbers. Ex)1,2,3\n");
			break;
		}

		/*
		http://www9.plala.or.jp/sgwr-t/lib/strtok.html
		*/
		splitted_p=strtok(input,delimiter);// 1��
		sum+=atoi(splitted_p);
		elem_num++;

		while(splitted_p != NULL){ //2�ڈȍ~
			splitted_p=strtok(NULL, delimiter);
			
			if(splitted_p!=NULL){
				sum+=atoi(splitted_p);
				elem_num++;
			}
		}
		
		//�o��
		printf("Sum: %d\n",sum);
		ave=sum/elem_num;
		printf("Ave: %d\n",ave);
	}

	return 0;
}


/*
�n���ꂽ������ɔ��p�����E�w��̋�؂蕶�����܂܂�Ă��Ȃ������肷��D
*/
int isIntArray(char* cArray, char* delimiter){
	char c;
	int i=0;
	int len=strlen(cArray);
	do{
		c=cArray[i];
		if(c<'0' || '9'<c){
			if(!isDelimiter(c,delimiter)){
				return 0;
			}
		}
	}while(++i<len);
	return 1;
}


/*
�n���ꂽ1��������؂蕶�����𔻒肷��i���������isIntArray()�ł��łɂ��Ă���j�D
*/
int isDelimiter(char c, char* delimiter){
	int i;
	int currentNotDelm=1; //delimiter�̍��̕����ƕs��v��������1
	for(i=0;i<strlen(delimiter);i++){
		/*
		https://dixq.net/forum/viewtopic.php?t=4764
		*/
		currentNotDelm=(delimiter[i]!=c);

		if(!currentNotDelm){ //��v�����؂蕶���������ꍇ
			break;
		}
	}

	if(currentNotDelm){ //delimiter�̂�����Ƃ���v���Ȃ�������currentNotDelm=1
		//printf("DelimiterError\n");
		return 0;
	}
	
	return 1;
}