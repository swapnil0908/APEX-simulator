#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *fp;
struct Code_Line
{
	char instruction_string[100];
	int address;
	struct Code_Line *next, *prev;
};
struct reg_to_value
{
	char reg[3];
	int value_in;
};

struct Register{
	int value;
	char *name;
};
struct Register reg[15];

struct Instruction_info
{
	int pc;
	int dest_num;
	int instruct_type;
	int dest_val;
	int src1_val;
	int src2_val;
	struct Instruction_info* next;
	struct Instruction_info* prev;
};
//int reg[15] = { '\0' };
int X = {'\0'};
int valid[15] = { 1 };
int address[1000] = { '\0' };
int valid_address[1000] = { 1 };
int adrs = 4000;
char *opcode;
char *input, *input1, *input2;
struct Instruction_info *d_ins_start = NULL, *d_ins_end = NULL, *d_ins_curr;
static struct Code_Line *start = NULL, *curr = NULL, *temp, *fetch_curr, *decode_curr, *execute_curr, *memory_curr, *writeback_curr, *mul1_curr, *mul2_curr, *temp_curr, *temp2_curr, *div1_curr, *div2_curr, *div3_curr, *div4_curr;
static int address_transfer = 0, mul_count=0, div_count=0, mul_flag=0, mul_fin_flag=0,stay_flag=0,jal_flag=0,jal_flag1=0,jal_flag2=0,stop_flag=0, jal_flag_m=0;
static int j;
int y=0;

void load()
{
	char line[100];
	while (fgets(line, 100, (FILE*)fp))
	{
		if (!start)
		{
			temp = malloc(sizeof(struct Code_Line));
			temp->next = NULL;
			temp->prev = NULL;
			strcpy(temp->instruction_string, line);
			adrs=adrs+4;
			temp->address = adrs;
			curr = temp;
			start = curr;
		}
		else
		{
			temp = malloc(sizeof(struct Code_Line));
			temp->next = NULL;
			temp->prev = curr;
			adrs=adrs+4;
			temp->address = adrs;
			strcpy(temp->instruction_string, line);
			curr->next = temp;
			curr = curr->next;
		}
	}
}
void idisplay()
{
	temp = start;
	while (temp != NULL)
	{
		printf("%d %s\n", temp->address, temp->instruction_string);
		temp = temp->next;
	}

}
void FETCH_1(){
					if (jal_flag2==2){
						printf("FETCH\t\t: EMPTY\n");
						jal_flag2=0;
						stop_flag=1;

					}


}
/*void TEMP2(int j){
	j=j-2;
	if (mul_fin_flag==1 && stay_flag==1){
		printf("DRF\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",temp2_curr->instruction_string);
		memory_curr = temp2_curr;
//		execute_curr = NULL;
}
		stay_flag=0;
j=j+2;
}
*/





void TEMP(int j){
	j=j-4;
	if (mul_fin_flag==1 && stay_flag==1){
		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",temp_curr->instruction_string);
		memory_curr = temp_curr;
//		stay_flag=0;
//		temp_curr = NULL;

j=j+4;


	}

}



int FETCH(struct Code_Line  *fetchptr, int j)
{
j=j-1;

if (fetch_curr!=NULL && stop_flag==0){
	printf("FETCH\t\t: ");
	printf("(I%d)\t",j);
//	printf("dec:%s\n",decode_curr->instruction_string);
	printf("%s\n",fetch_curr->instruction_string);
			decode_curr = fetch_curr;
			//fetch_curr = NULL;
			return 1;
}

else return 0;

j=j+1;
}
struct Instruction_info* search_curr_decoded_ins(int address)
{
	struct Instruction_info* temp;
	temp = d_ins_end;
	while (temp)
	{
		if (temp->pc == address)
		{
			return temp;
		}
		else
		{
			temp = temp->prev;
		}
	}
}
int check_type_of_ins(struct Code_Line *instruction)
{
	int type = 0;
	char* ins;

	char *decode_curr_str = (char*)malloc(sizeof(char) * 10);
	strcpy(decode_curr_str, instruction->instruction_string);
	if (!strncmp(opcode, "MOVC", 4) || !strncmp(opcode, "MOV", 3)) { return 1; }
	else if (!strncmp(opcode, "ADD", 3))	{ return 2; }
	else if (!strncmp(opcode, "SUB", 3))	{ return 3; }
	else if (!strncmp(opcode, "DIV", 3))	{ return 4; }
	else if (!strncmp(opcode, "MUL", 3))	{ return 5; }
	else if (!strncmp(opcode, "LOAD", 4))	{ return 6; }
	else if (!strncmp(opcode, "STORE", 5))	{ return 7; }
	else if (!strncmp(opcode, "BZ", 2)) 	{ return 8; }
	else if (!strncmp(opcode, "BNZ", 3))	{ return 9; }
	else if (!strncmp(opcode, "JUMP", 4))	{ return 10; }
	else if (!strncmp(opcode, "JAL", 3))	{ return 11; }
	else if (!strncmp(opcode, "HALT", 4))	{ return 12; }
	else if (!strncmp(opcode, "NOP", 3))	{ return 13; }
	else  { return 14; }

	//free(decode_curr_str);
}

void DECODE(int j)
{
	int dest = '\0', reg1 = '\0', reg2 = '\0';
	char *dest_reg, *register1, *register2;
	j=j-2;

	if (decode_curr)
	{
		if (!execute_curr)
		{
			if (jal_flag==1){
				printf("DRF\t\t: ");
				printf("EMPTY\n");
				jal_flag2=2;
			}


		else if	(mul_fin_flag!=1 && stay_flag!=1 && jal_flag!=1){
		printf("DRF\t\t: ");
		printf("(I%d)\t",j);
		printf("%s",decode_curr->instruction_string);}

			char *decode_curr_str = (char*)malloc(sizeof(char) * 10);
			strcpy(decode_curr_str, decode_curr->instruction_string);
			opcode = strtok(decode_curr_str, " ,#");
			if (!strncmp(opcode, "MOVC", 4))
			{
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");

			for(y=0;y<16;y++){
				if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
				if (valid[y] == 1)
				{
					valid[y] = 0;
					int index = decode_curr->address - 4000;
					struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
					temp_ins->instruct_type = check_type_of_ins(decode_curr);
					temp_ins->dest_num = y;
					temp_ins->src1_val = atoi(register1);
					temp_ins->pc = decode_curr->address;
					temp_ins->next = NULL;
					temp_ins->prev = NULL;
					if (!d_ins_start)
					{
						d_ins_start = temp_ins;
						d_ins_end = temp_ins;
						d_ins_curr = d_ins_start;
					}
					else
					{
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;

					}


					}
				}
			}




					execute_curr = decode_curr;
					decode_curr = NULL;




			}
			else if (!strncmp(opcode, "MOV", 3))
			{
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");

			for(y=0;y<16;y++){
				if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
				if (valid[dest] == 1)
				{
					valid[dest] = 0;
					int index = decode_curr->address - 4000;
					struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
					temp_ins->instruct_type = check_type_of_ins(decode_curr);
					temp_ins->dest_num = y;
					temp_ins->src1_val = atoi(register1);
					temp_ins->pc = decode_curr->address;
					temp_ins->next = NULL;
					temp_ins->prev = NULL;
					if (!d_ins_start)
					{
						d_ins_start = temp_ins;
						d_ins_end = temp_ins;
						d_ins_curr = d_ins_start;
					}
					else
					{
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;

					}
					execute_curr = decode_curr;
					decode_curr = NULL;

					}
				}
			}



		}

			else if (!strncmp(opcode, "ADD", 3) || !strncmp(opcode, "SUB", 3) || !strncmp(opcode, "MUL", 3) || !strncmp(opcode, "DIV", 3))
			{
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");
				register2 = strtok(NULL, " ,#");
				struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				for(y=0;y<16;y++){
				if (register1!=NULL && strcmp(register1,reg[y].name)==0){
				if (valid[y] == 1)
				{
					temp_ins->src1_val = reg[y].value;
			//		printf("reg1_value=%d\n",reg[y].value);
			//		printf("reg1_value=%d\n",temp_ins->src1_val);

						}
					}
				}


					for(y=0;y<16;y++){

					if (register2!=NULL && strcmp(register2,reg[y].name)==0 || register2!=NULL && strcmp(register2,reg[y].name)==10){
						if (valid[y] == 1)
						{
								temp_ins->src2_val = reg[y].value;
				//				printf("reg2_value=%d\n",reg[y].value);
				//	printf("reg2_value=%d\n",temp_ins->src2_val);
					}
						}
					else	 if	(register2!=NULL){
							temp_ins->src2_val = atoi(register2);
								}
							}



					for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{
					valid[y] = 0;
					temp_ins->instruct_type = check_type_of_ins(decode_curr);
					temp_ins->dest_num = y;
					temp_ins->pc = decode_curr->address;
					temp_ins->next = NULL;
					d_ins_curr->next = temp_ins;
					temp_ins->prev = d_ins_curr;
					d_ins_curr = d_ins_curr->next;
					execute_curr = decode_curr;
					decode_curr = NULL;
							}
						}
					}
			}




			else if (!strncmp(opcode, "LOAD", 4))
			{
				struct Instruction_info* temp_instruct = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");
				register2 = strtok(NULL, " ,#");



					for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{
						valid[y] = 0;
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(decode_curr);
						temp_ins->dest_num = y;

							}
						}
					}

				for(y=0;y<16;y++){
						if (register1!=NULL && strcmp(register1,reg[y].name)==0){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src1_val = reg[y].value;
							}
						}
					}

				for(y=0;y<16;y++){
						if (register2!=NULL){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src2_val = reg[y].value;
							}
						}
					}

						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->pc = decode_curr->address;
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;

			}



			else if (!strncmp(opcode, "STORE", 5))
			{
	struct Instruction_info* temp_instruct = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");
				register2 = strtok(NULL, " ,#");



				for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{
						valid[y] = 0;
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(decode_curr);
						temp_ins->dest_num = y;

							}
						}
					}

				for(y=0;y<16;y++){
						if (register1!=NULL && strcmp(register1,reg[y].name)==0){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src1_val = reg[y].value;
							}
						}
					}

				for(y=0;y<16;y++){
						if (register2!=NULL){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src2_val = reg[y].value;
							}
						}
					}

						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->pc = decode_curr->address;
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;


			}



			else if (!strncmp(opcode, "HALT", 4))
			{
				struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				temp_ins->instruct_type = check_type_of_ins(decode_curr);
				temp_ins->pc = decode_curr->address;
				temp_ins->next = NULL;
				d_ins_curr->next = temp_ins;
				temp_ins->prev = d_ins_curr;
				d_ins_curr = d_ins_curr->next;
				execute_curr = decode_curr;
				decode_curr = NULL;
			}


			else if (!strncmp(opcode, "NOP", 4))
			{
				struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				temp_ins->instruct_type = check_type_of_ins(decode_curr);
				temp_ins->pc = decode_curr->address;
				temp_ins->next = NULL;
				d_ins_curr->next = temp_ins;
				temp_ins->prev = d_ins_curr;
				d_ins_curr = d_ins_curr->next;
				execute_curr = decode_curr;
				decode_curr = NULL;

			}
			else if (!strncmp(opcode, "JAL", 3))
			{

				struct Code_Line* ltemp;
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");
				register2 = strtok(NULL, " ,#");

					for(y=0;y<16;y++){
						if (register1!=NULL && strcmp(register1,reg[y].name)==0){
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
		//				printf("regval:%d\n",reg[y].value);
		//				printf("regname:%d\n",y);
		//				printf("reg2:%d\n",atoi(register2));
						X=reg[y].value + atoi(register2);
							}
						}




		//		printf("X:%d\n",X);
				jal_flag2=1;
				ltemp = start;
				while (ltemp != NULL && ltemp->address != X)
				{
					ltemp = ltemp->next;
				}
				if (ltemp)
				{
					char* ltemp_instr = (char*)malloc(sizeof(char) * 10);
					strcpy(ltemp_instr, ltemp->instruction_string);
					opcode = strtok(ltemp_instr, " ,#");
				//	printf("y:%s\n",ltemp->instruction_string);
					int new_type = check_type_of_ins(ltemp);
					if (new_type == 1)
					{
						dest_reg = strtok(NULL, " ,#");
						register1 = strtok(NULL, " ,#");

						for(y=0;y<16;y++){
						if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){

						if (valid[y] == 1)
						{
							valid[y] = 0;
							int index = decode_curr->address - 4000;
							struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
							temp_ins->instruct_type = check_type_of_ins(ltemp);
							temp_ins->dest_num = y;

							if (strncmp(register1, "X", 1))
							{
								temp_ins->src1_val = X;
							}
							else
							{
								temp_ins->src1_val = atoi(register1);
							}
							temp_ins->pc = decode_curr->address;
							temp_ins->next = NULL;
							temp_ins->prev = NULL;
							if (!d_ins_start)
							{
								d_ins_start = temp_ins;
								d_ins_end = temp_ins;
								d_ins_curr = d_ins_start;
							}
							else
							{
								d_ins_curr->next = temp_ins;
								temp_ins->prev = d_ins_curr;
								d_ins_curr = d_ins_curr->next;

							}
						//	jal_flag=1;
							execute_curr = decode_curr;
							decode_curr = NULL;
						//	printf("j_Flag:%d\n",jal_flag);
								}
							}
						}
					}



					else if (new_type >= 2 && new_type <= 5)
					{

						dest_reg = strtok(NULL, " ,#");
						register1 = strtok(NULL, " ,#");
						register2 = strtok(NULL, " ,#");
							struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				for(y=0;y<16;y++){
				if (register1!=NULL && strcmp(register1,reg[y].name)==0){
				if (valid[y] == 1)
				{
					temp_ins->src1_val = reg[y].value;

						}
					}
				}


					for(y=0;y<16;y++){
					if (register2!=NULL && strcmp(register2,reg[y].name)==0){
						if (valid[y] == 1)
						{
								temp_ins->src2_val = reg[y].value;
							}
						}
						else if	(register2!=NULL){
							temp_ins->src2_val = atoi(register2);
								}
							}



					for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{
									if (valid[y] == 1)
									{
										valid[y] = 0;
										struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
										temp_ins->instruct_type = check_type_of_ins(ltemp);
										temp_ins->dest_num = y;
										temp_ins->pc = decode_curr->address;
										temp_ins->next = NULL;
										d_ins_curr->next = temp_ins;
										temp_ins->prev = d_ins_curr;
										d_ins_curr = d_ins_curr->next;
										execute_curr = decode_curr;
										decode_curr = NULL;
									}
								}
							}
						}
					}




					else if (new_type == 6)
					{

						dest_reg = strtok(NULL, " ,#");
						register1 = strtok(NULL, " ,#");
						register2 = strtok(NULL, " ,#");

				for(y=0;y<16;y++){
						if (register1!=NULL && strcmp(register1,reg[y].name)==0){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src1_val = reg[y].value;
							}
						}
					}

				for(y=0;y<16;y++){
						if (register2!=NULL){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src2_val = atoi(register2);
							}
						}
					}

				for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
						if (valid[y] == 1)
							{
								valid[y] = 0;
								struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
								temp_ins->instruct_type = check_type_of_ins(ltemp);
								temp_ins->dest_num = y;
								temp_ins->pc = decode_curr->address;
								temp_ins->next = NULL;
								d_ins_curr->next = temp_ins;
								temp_ins->prev = d_ins_curr;
								d_ins_curr = d_ins_curr->next;
								execute_curr = decode_curr;
								decode_curr = NULL;
							}

						}


					}
				}
					else if (new_type == 7)
					{
												dest_reg = strtok(NULL, " ,#");
						register1 = strtok(NULL, " ,#");
						register2 = strtok(NULL, " ,#");

				for(y=0;y<16;y++){
						if (register1!=NULL && strcmp(register1,reg[y].name)==0){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src1_val = reg[y].value;
							}
						}
					}

				for(y=0;y<16;y++){
						if (register2!=NULL){
						if (valid[y] == 1)
						{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->src2_val = atoi(register2);
							}
						}
					}

				for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
						if (valid[y] == 1)
							{
								valid[y] = 0;
								struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
								temp_ins->instruct_type = check_type_of_ins(ltemp);
								temp_ins->dest_num = y;
								temp_ins->pc = decode_curr->address;
								temp_ins->next = NULL;
								d_ins_curr->next = temp_ins;
								temp_ins->prev = d_ins_curr;
								d_ins_curr = d_ins_curr->next;
								execute_curr = decode_curr;
								decode_curr = NULL;
								}

							}


						}

					}
					else if (new_type == 12 || new_type == 14)
					{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(ltemp);
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;

					}
					else if (new_type == 8)
					{
						dest_reg = strtok(NULL, " ,#");
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(ltemp);
						temp_ins->dest_val = atoi(dest_reg);
						temp_ins->pc = decode_curr->address;
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;

					}
					else if (new_type == 9)
					{
						dest_reg = strtok(NULL, " ,#");
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(ltemp);
						temp_ins->dest_val = atoi(dest_reg);
						temp_ins->pc = decode_curr->address;
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;
					}
					else if (new_type == 11)
					{
						printf("\nJAL after JAL exception\n");
					}
					else
					{
						dest_reg = strtok(NULL, " ,#");
						register1 = strtok(NULL, " ,#");

					for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{
							valid[y] = 0;
							struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
							temp_ins->instruct_type = check_type_of_ins(decode_curr);
							temp_ins->dest_num = y;
							}
						}
					}

					for(y=0;y<16;y++){
					if (register1!=NULL && strcmp(register1,reg[y].name)==0){
					if (valid[y] == 1)
					{
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
							temp_ins->src1_val = atoi(register1);
							}
						}
					}

					struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
							temp_ins->pc = decode_curr->address;
							temp_ins->next = NULL;
							if (!d_ins_start)
							{
								d_ins_start = temp_ins;
								d_ins_curr = d_ins_start;
							}
							else
							{
								d_ins_curr->next = temp_ins;
								d_ins_curr = d_ins_curr->next;

							}
							execute_curr = decode_curr;
							decode_curr = NULL;

						}

					}
				}

			else if (!strncmp(opcode, "JUMP", 4))
			{
				dest_reg = strtok(NULL, " ,#");
				register1 = strtok(NULL, " ,#");
					for(y=0;y<16;y++){
					if (dest_reg!=NULL && strcmp(dest_reg,reg[y].name)==0){
					if (valid[y] == 1)
					{

						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->instruct_type = check_type_of_ins(decode_curr);
						temp_ins->dest_val = reg[y].value + atoi(register1);
							}
						}
					else if(register1==NULL){
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->dest_val = atoi(dest_reg);
						}
					}
						struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
						temp_ins->pc = decode_curr->address;
						temp_ins->next = NULL;
						d_ins_curr->next = temp_ins;
						temp_ins->prev = d_ins_curr;
						d_ins_curr = d_ins_curr->next;
						execute_curr = decode_curr;
						decode_curr = NULL;
					}

			else if (!strncmp(opcode, "BZ", 2))
			{
				dest_reg = strtok(NULL, " ,#");
				struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				temp_ins->instruct_type = check_type_of_ins(decode_curr);
				temp_ins->dest_val = atoi(dest_reg);
				temp_ins->pc = decode_curr->address;
				temp_ins->next = NULL;
				d_ins_curr->next = temp_ins;
				temp_ins->prev = d_ins_curr;
				d_ins_curr = d_ins_curr->next;
				execute_curr = decode_curr;
				decode_curr = NULL;
			}
			else if (!strncmp(opcode, "BNZ", 3))
			{
				dest_reg = strtok(NULL, " ,#");
				struct Instruction_info* temp_ins = (struct Instruction_info*)malloc(sizeof(struct Instruction_info));
				temp_ins->instruct_type = check_type_of_ins(decode_curr);
				temp_ins->dest_val = atoi(dest_reg);
				temp_ins->pc = decode_curr->address;
				temp_ins->next = NULL;
				d_ins_curr->next = temp_ins;
				temp_ins->prev = d_ins_curr;
				d_ins_curr = d_ins_curr->next;
				execute_curr = decode_curr;
				decode_curr = NULL;
			}

			else
			{
				printf("Wrong instruction entered %s\n", opcode);
			}

			d_ins_end = d_ins_curr;
		}
	}
	else{printf("DRF\t\t: EMPTY\n");}
	j=j+2;
}
void execute_ins(struct Instruction_info* exec_ins,int j)
{

	struct Instruction_info* temp_check;
	struct Code_Line* next_fetch = start;
	int type = exec_ins->instruct_type;
	if (jal_flag2==1){
		type=11;
	}

	if(jal_flag_m==1){
		type=17; //random
	}

	switch (type)
	{

	case 1:
	//MOV

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val;
	//	printf("!!!value3:%d\n",exec_ins->dest_val);
		if (mul_flag!=1){
		memory_curr = execute_curr;
		execute_curr = NULL;
		}

		break;

	case 2:
		//ADD

	if (mul_flag==0 &&div_count==0){
 		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val + exec_ins->src2_val;
		memory_curr = execute_curr;
		temp_curr = execute_curr;
		execute_curr = NULL;
		}


else if(div_count!=0){
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val + exec_ins->src2_val;
		memory_curr = execute_curr;
		temp_curr = execute_curr;
		execute_curr = NULL;
}
		break;


	case 3:
	//SUB

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val - exec_ins->src2_val;
		memory_curr = execute_curr;
		execute_curr = NULL;
		break;
	case 4:
	//DIV
		exec_ins->dest_val = exec_ins->src1_val / exec_ins->src2_val;
		div1_curr = execute_curr;
		execute_curr = NULL;
		div_count=1;
		break;
	case 5:
	//MUL
		exec_ins->dest_val = exec_ins->src1_val * exec_ins->src2_val;
		mul1_curr = execute_curr;
		execute_curr = NULL;
		mul_count=1;
		break;

	case 6:
	//LOAD

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val + exec_ins->src2_val;
		memory_curr = execute_curr;
		execute_curr = NULL;
		break;
	case 7:
	//STORE

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		exec_ins->dest_val = exec_ins->src1_val + exec_ins->src2_val;
		valid_address[exec_ins->dest_val] = 0;
		memory_curr = execute_curr;
		execute_curr = NULL;
		break;
	case 8:
	//BZ

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		temp_check = d_ins_start;
		while (temp_check->pc != (execute_curr->address - 1))
		{
			temp_check = temp_check->next;
		}
		if (valid[temp_check->dest_num] == 1)
		{
			if (reg[temp_check->dest_num].value == 0)
			{
				int pc_add = exec_ins->dest_val;
				pc_add = execute_curr->address + pc_add;
				struct Code_Line* next_fetch = start;
				while (next_fetch->address != pc_add)
				{
					next_fetch = next_fetch->next;
				}
				fetch_curr = next_fetch;
				decode_curr = NULL;
				execute_curr = NULL;
			}
			else
			{
				execute_curr = NULL;
			}
		}
		break;
	case 9:
	//BNZ

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		temp_check = d_ins_start;
		while (temp_check->pc != (execute_curr->address - 1))
		{
			temp_check = temp_check->next;
		}
		if (valid[temp_check->dest_num] == 1)
		{
			if (reg[temp_check->dest_num].value != 0)
			{
				int pc_add = exec_ins->dest_val;
				pc_add = execute_curr->address + pc_add;
				struct Code_Line* next_fetch = start;
				while (next_fetch->address != pc_add)
				{
					next_fetch = next_fetch->next;
				}
				fetch_curr = next_fetch;
				decode_curr = NULL;
				execute_curr = NULL;
			}
			else
			{
				execute_curr = NULL;
			}
		}
		break;
	case 10:
	//jump

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		next_fetch = start;
		while (next_fetch->address != exec_ins->pc)
		{
			next_fetch = next_fetch->next;
		}
		fetch_curr = next_fetch;
		decode_curr = NULL;
		execute_curr = NULL;

		break;
	case 11:
	//JAL

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		jal_flag=1;
		jal_flag1=1;

//		printf("exec_jal_flag:%d\n",jal_flag);
//		printf("exec_jal_flag1:%d\n",jal_flag1);
		memory_curr = execute_curr;
		execute_curr = NULL;
		break;
	case 12:
	//HALT

		printf("DIV4\t\t: ");
		printf("EMPTY\n");
		printf("DIV3\t\t: ");
		printf("EMPTY\n");
		printf("DIV2\t\t: ");
		printf("EMPTY\n");
		printf("DIV1\t\t: ");
		printf("EMPTY\n");
		printf("MUL2\t\t: ");
		printf("EMPTY\n");
		printf("MUL1\t\t: ");
		printf("EMPTY\n");
		printf("INTFU\t\t:");
		printf(" (I%d)\t",j);
		printf("%s",execute_curr->instruction_string);
		if (!memory_curr)
		{
			if (!writeback_curr)
			{
				memory_curr = execute_curr;
				execute_curr = NULL;
			}
		}
		break;
	case 13:
//	NOP
		execute_curr = NULL;
		break;


	default:
		break;
	}


}


void EXECUTE(int j)
{
j=j-3;

	if (execute_curr)
	{
		if (!memory_curr)
		{
			if (execute_curr->address == d_ins_curr->pc)
			{
				d_ins_curr->instruct_type;
				execute_ins(d_ins_curr,j);

			}
			else
			{
				struct Instruction_info* temp_decoded = search_curr_decoded_ins(execute_curr->address);
				execute_ins(temp_decoded,j);

			}
		}
	}

	else if(mul_fin_flag==0){
			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			printf("MUL2\t\t: ");
			printf("EMPTY\n");
			printf("MUL1\t\t: ");
			printf("EMPTY\n");
			printf("INTFU\t\t: ");
			printf("EMPTY\n");

	}


		if(jal_flag_m==1){
			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			printf("MUL2\t\t: ");
			printf("EMPTY\n");
			printf("MUL1\t\t: ");
			printf("EMPTY\n");
			printf("INTFU\t\t: ");
			printf("EMPTY\n");

	}

j=j+3;

}


void DIV1(int j){
	j=j-3;

	if (div_count==1) {


			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",div1_curr->instruction_string);
			printf("MUL2\t\t: ");
			printf("EMPTY\n");
			printf("MUL1\t\t: ");
			printf("EMPTY\n");
			printf("INTFU\t\t: ");
			printf("EMPTY\n");
			div_count=2;
			div2_curr = div1_curr;
	}
	j=j+3;

}


void DIV2(int j){
	j=j-4;
	if (div_count==2) {


			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",div2_curr->instruction_string);
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			div_count=3;
			div3_curr = div2_curr;
	}
	j=j+4;

}

void DIV3(int j){
	j=j-5;
	if (div_count==3) {


			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",div3_curr->instruction_string);
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			div_count=4;
			div4_curr = div3_curr;
	}
	j=j+5;

}


void DIV4(int j){
	j=j-6;
	if (div_count==4) {


			printf("DIV4\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",div4_curr->instruction_string);
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			div_count=0;
			memory_curr = div4_curr;
	}
	j=j+6;

}






void MUL1(int j){
//	printf("asda%s\n",mul1_curr->instruction_string);
j=j-3;
	if (mul_count==1) {


			printf("DIV4\t\t: ");
			printf("EMPTY\n");
			printf("DIV3\t\t: ");
			printf("EMPTY\n");
			printf("DIV2\t\t: ");
			printf("EMPTY\n");
			printf("DIV1\t\t: ");
			printf("EMPTY\n");
			printf("MUL2\t\t: ");
			printf("EMPTY\n");
			printf("MUL1\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",mul1_curr->instruction_string);
			printf("INTFU\t\t: ");
			printf("EMPTY\n");
			mul_count=2;
			mul2_curr = mul1_curr;
	}
	j=j+3;

}

void MUL2(int j){
//	printf("asda%s\n",mul1_curr->instruction_string);

	if (mul_count==2) {
			j=j-4;
			printf("MUL2\t\t: ");
			printf("(I%d)\t",j);
			printf("%s",mul2_curr->instruction_string);
			printf("MUL1\t\t: ");
			printf("EMPTY\n");
			mul_count=0;
			mul_flag=1;
			memory_curr = mul2_curr;
			mul_fin_flag=1;
			stay_flag=1;
			j=j+4;
	}

}


int mem_stage(struct Instruction_info* temp_ins, struct Code_Line* ms_curr)
{

	if (temp_ins->instruct_type == 7)
	{
		if (valid_address[temp_ins->dest_val] == 1)
		{
			reg[temp_ins->dest_num].value = address[temp_ins->dest_val];
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else if (temp_ins->instruct_type == 8)
	{

		address[temp_ins->dest_val] = reg[temp_ins->dest_num].value;
		valid_address[temp_ins->dest_val] = 1;
		return 1;
	}
	return 1;
}
void MEMORY(int j)

{
if (mul_fin_flag!=1){
	j=j-4;
}
else if(mul_fin_flag==1){
	j=j-5;

}
	if (memory_curr)
	{
		if (!writeback_curr)
		{
			printf("MEM\t\t: ");
	//		j=j-4;
			printf("(I%d)\t",j);
			printf("%s",memory_curr->instruction_string);
			//ins = (char*)malloc(sizeof(char) * 5);
			char *memory_curr_str = (char*)malloc(sizeof(char) * 10);
			strcpy(memory_curr_str, memory_curr->instruction_string);
			opcode = strtok(memory_curr_str, " ,#");
			int fs = 0;
			if(!strncmp(opcode, "JAL", 3)){
				stop_flag=0;
				jal_flag_m=1;

			}
			if (!strncmp(opcode, "STORE", 5) || !strncmp(opcode, "LOAD", 4))
			{
				if (memory_curr->address == d_ins_curr->pc)
				{

					fs = mem_stage(d_ins_curr, memory_curr);
				}
				else
				{
					struct Instruction_info* temp_decoded = search_curr_decoded_ins(memory_curr->address);
					fs = mem_stage(temp_decoded, memory_curr);
				}
				if (fs == 1)
				{
					writeback_curr = memory_curr;
					memory_curr = NULL;
				}

			}
			//free(ins);
			else
			{
				writeback_curr = memory_curr;
				memory_curr = NULL;
			}

			//	free(memory_curr_str);
		}
	if (mul_fin_flag!=1){
	j=j+4;
}
else if (mul_fin_flag==1){
	j=j+5;
}
	}
	else{printf("MEM\t\t: EMPTY\n");}
}
void write_back(struct Instruction_info* temp_decoded)
{
	if ((temp_decoded->instruct_type != 7 )&& (temp_decoded->instruct_type != 8 )&& (temp_decoded->instruct_type != 13))
	{
		reg[temp_decoded->dest_num].value = temp_decoded->dest_val;

//		printf("value:%d\n",temp_decoded->dest_val);
//		printf("num:%d\n",temp_decoded->dest_num);

		valid[temp_decoded->dest_num] = 1;
	}
	else if (temp_decoded->instruct_type == 7)
	{
		valid[temp_decoded->dest_num] = 1;
	}
}
void WRITEBACK(int j)
{
	if (mul_fin_flag!=1){
	j=j-5;
}
else if(mul_fin_flag==1){
	j=j-6;

}

	if (writeback_curr)
	{
			printf("WB\t\t: ");
	//		j=j-5;
			printf("(I%d)\t",j);
			printf("%s",writeback_curr->instruction_string);
		if (writeback_curr->address == d_ins_curr->pc)
		{
			write_back(d_ins_curr);
		}
		else
		{
			struct Instruction_info* temp_decoded = search_curr_decoded_ins(writeback_curr->address);
			write_back(temp_decoded);
		}
		writeback_curr = NULL;

	}
	else{printf("WB\t\t: EMPTY\n");}

	if (mul_fin_flag!=1){
	j=j+5;
}
else if(mul_fin_flag==1){
	j=j+6;

}
//mul_fin_flag=0;
}

int main()
{
	int i = 1, j;


	while (i != 0)
	{
		printf("\nPlease give the input from the following commands:\n\tload\n\tinitialize\n\tsimulate\n\tdisplay\n\tquit\n");
		input = (char*)malloc(sizeof(char) * 40);
		fgets(input, 40, stdin);
		if (!strncmp(input, "quit", 4))
		{
			i = 0;

		}
		else if (!strncmp(input, "load", 4))
		{
			printf("\n In load\n");
			//instr1 = (char*)malloc(40 * sizeof(char));
			//instr2 = (char*)malloc(40 * sizeof(char));

			strcat(input, " ");

			input1 = strtok(input, " ,#");
			input2 = strtok(NULL, " ,#");
			//free(instr2);
			if (input2 != NULL)
			{

				input2[strlen(input2) - 1] = '\0';

				fp = fopen(input2, "r");
				load();
				idisplay();
				printf("\nAll Instructions Loaded done\n");
				fclose(fp);
			}
			else
			{
				printf("\nPlease enter the command in the format load <filename>");
			}
			//instr2[strlen(instr2)] = '\n';
			//free(instr1);
		}
		else if (!strncmp(input, "initialize", 10))
		{

			fetch_curr = start;
			decode_curr = NULL;
			execute_curr = NULL;
			memory_curr = NULL;
			writeback_curr = NULL;
			d_ins_curr = NULL;
			d_ins_start = NULL;
			d_ins_end = NULL;
			for (i = 0; i < 16; i++)
			{
				reg[i].value = NULL;
				valid[i] = 1;
			}
			for (i = 0; i < 1000; i++)
			{
				valid_address[i] = 1;
				address[i] = '\0';
			}

	reg[0].name="R0";
  	reg[1].name="R1";
   	reg[2].name="R2";
    reg[3].name="R3";
    reg[4].name="R4";
    reg[5].name="R5";
    reg[6].name="R6";
	reg[7].name="R7";
    reg[8].name="R8";
    reg[9].name="R9";
    reg[10].name="R10";
    reg[11].name="R11";
    reg[12].name="R12";
    reg[13].name="R13";
    reg[14].name="R14";
    reg[15].name="R15";

			printf("\nREGISTER VALUES, STATUSES AND DATA MEMORY INITIALIZED...\n");
		}
		else if (!strncmp(input, "simulate", 8))
		{
			int n, status;
			printf("\nIn simulate\n");
			//instr1 = (char*)calloc(40, sizeof(char));
			//instr2 = (char*)calloc(40, sizeof(char));
			strcat(input, " ");
			input1 = strtok(input, " ,#");
			input2 = strtok(NULL, " ,#");
			if (input2 != NULL)
			{
				input2[strlen(input2) - 1] = '\0';
				n = atoi(input2);
				printf("\nRunning for %d Cycles\n",n);
				for (j = 1; j <= n; j++)

				{

					printf("cycle: %d\n",j);
					WRITEBACK(j);
					MEMORY(j);

					TEMP(j);
					EXECUTE(j);

					DIV4(j);
					DIV3(j);
					DIV2(j);
					DIV1(j);
					MUL2(j);
					MUL1(j);
				//	TEMP2(j);
					DECODE(j);
				//	printf("jal_flag:%d\n",jal_flag);
					FETCH_1();
					status = FETCH(fetch_curr,j);


					if (status == 1 && jal_flag2==0)
					{
						fetch_curr = fetch_curr->next;
					}

					else if(stop_flag==0){

						fetch_curr  =  start;
						while (fetch_curr != NULL && fetch_curr->address != X)
						{
					fetch_curr = fetch_curr->next;

						}
						if(jal_flag_m==1){

						stop_flag==1;
						jal_flag2==0;
					}
				}


				}

			}
			else { printf("\nPlease enter the command in the format simulate <number of cycles>"); }

		}
		else if (!strncmp(input, "display", 7))
		{
			printf("\nREGISTER VALUES \n");
			int i;
			printf("***********************************************************************************************************************************\n");
			for (i = 0; i < 16; i++)
			{
				if (!(i % 8))
				{
					printf("\n");
				}
				printf("R[%02d]=%02d ", i, reg[i].value);
			}


	printf("\n");
	printf("\nMEMORY VALUES \n");
	printf("***********************************************************************************************************************************\n");
			for (i = 0; i <= 100; i=i+4)
			{
				if (!(i % 10))
				{
					printf("\n");
				}
				printf("Mem[%04d]=%04d ", i, address[i]);
			}
	//		printf("\n***********************************************************************************************************************************\n");
		}
		free(input);


	}
	return 0;
}

