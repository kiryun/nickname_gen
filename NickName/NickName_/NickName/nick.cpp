#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;


//NULL�� ���ԵǾ��ִ� �迭 ���� ��ȯ �Լ�
template<typename T>
int ArrLen(T* arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		i++;
	}
	return i;
}

template<typename T>
void BackUpOrRecovery(T* data1, T* data2, int len)
{
	for (int i = 0; i < len; i++)
	{
		data1[i] = data2[i];
	}
}
// ��ҹ��� ���� ���� ���� �Լ�
void Division(uint8_t* result_untidy, uint8_t* Consonant, uint8_t* consonant, uint8_t* vowel)//, int* Consonant_len = 0, int* consonant_len = 0, int* vowel_len = 0 )
{
	int Consonant_len = 0; //���� �빮�� ����
	int consonant_len = 0; //���� �ҹ��� ����
	int vowel_len = 0; // ���� ����

					   //��ҹ��� ���� ���� ����
	int i = 0;
	while (result_untidy[i] != NULL)
	{
		if ((result_untidy[i] == 'a') ||
			(result_untidy[i] == 'e') ||
			(result_untidy[i] == 'o') ||
			(result_untidy[i] == 'u') ||
			(result_untidy[i] == 'i') ||
			(result_untidy[i] == 'y'))
		{
			/*// �빮�� �ϰ��
			if (result_untidy[i] >= 0x41 && result_untidy[i] <= 0x5a)
			{
			result_untidy[i] += 0x20;
			}*/
			vowel[vowel_len] = result_untidy[i];
			(vowel_len)++;
		}
		// �빮���� ���
		else if ((result_untidy[i] >= 0x41 && result_untidy[i] <= 0x5a))
		{
			Consonant[Consonant_len] = result_untidy[i];
			(Consonant_len)++;
		}
		// ������ �ƴϸ鼭 �ҹ����� ���
		else if ((result_untidy[i] >= 0x61 && result_untidy[i] <= 0x7a) &&
			!((result_untidy[i] == 'a') ||
			(result_untidy[i] == 'e') ||
				(result_untidy[i] == 'o') ||
				(result_untidy[i] == 'u') ||
				(result_untidy[i] == 'i') ||
				(result_untidy[i] == 'y')))
		{
			consonant[consonant_len] = result_untidy[i];
			//printf("%c", result_untidy[i]); // debug log
			//printf("%c , ", consonant[*consonant_len]); //debug log
			(consonant_len)++;
		}
		i++; // while ��
	}
	//�빮�� ���� �ߺ� ����
	for (int i = 0; i < ArrLen(Consonant); i++)
	{
		for (int j = 0; j < ArrLen(Consonant); j++)
		{
			if (i != j)
			{
				if (Consonant[i] == Consonant[j])
				{
					Consonant[j] = NULL;
				}
			}
		}
	}
	//���� �ߺ� ����
	for (int i = 0; i < ArrLen(vowel); i++)
	{
		for (int j = 0; j < ArrLen(vowel); j++)
		{
			if (i != j)
			{
				if (vowel[i] == vowel[j])
				{
					vowel[j] = NULL;
				}
			}
		}
	}
}

//�г��� ���̸� �������ִ� �Լ�
void SelectNickNameLen(uint8_t* vowel, int* result_len)
{
	// ������ ������ 3�� �̻�
	if (ArrLen(vowel) >= 3)
	{
		*result_len = 7;
	}
	else
	{
		int input = 0;
		int len = 0;

		cout << "���� ������ �ʹ� ��� ����ڰ� ���ϴ� ���� �Է�(�ߺ�x)" << endl;

		while (ArrLen(vowel) != 2)
		{
			input = 0;
			printf("���� ������ �ִ� ���� : %s \n", vowel);
			cout << "1. \"a\"  2. \"e\"  3. \"i\"  4. \"o\"  5. \"u\"  6. \"y\"" << endl;

			scanf("%d", &input); // ���� �Է����� ��� ���� while�� ����

			fflush(stdin);
			switch (input)
			{
			case 1:
				if (vowel[0] != 'a')
				{
					vowel[ArrLen(vowel)] = 'a';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			case 2:
				if (vowel[0] != 'e')
				{
					vowel[ArrLen(vowel)] = 'e';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			case 3:
				if (vowel[0] != 'i')
				{
					vowel[ArrLen(vowel)] = 'i';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			case 4:
				if (vowel[0] != 'o')
				{
					vowel[ArrLen(vowel)] = 'o';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			case 5:
				if (vowel[0] != 'u')
				{
					vowel[ArrLen(vowel)] = 'u';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			case 6:
				if (vowel[0] != 'y')
				{
					vowel[ArrLen(vowel)] = 'y';
				}
				else
				{
					cout << "�߸� �Է�(�ߺ�x)" << endl;
				}
				break;
			default:
				cout << "�߸� �Է� 1~5" << endl;
				break;
			}
			*result_len = 5;
		}
	}
}

//���ڹ迭 �Լ�
void Arrange(uint8_t* Consonant, uint8_t* consonant, uint8_t* vowel, uint8_t* result, int* overlap, int result_len, char ex_word)
{
	//���� : a e i o u y
	//���� : ������

	//result�� �ƹ��͵� ���ٸ�
	if (ArrLen(result) == 0)
	{
		for (int i = 0; i < ArrLen(Consonant); i++)
		{

			//���
			uint8_t* temp_result = NULL;
			int* temp_overlap = NULL;

			temp_result = (uint8_t*)malloc(sizeof(uint8_t)*(result_len + 1));
			temp_overlap = (int*)malloc(sizeof(int)*ArrLen(consonant));

			/*for (int i = 0; i < result_len + 1; i++)
			{
			temp_result[i] = result[i];
			}
			for (int i = 0; i < ArrLen(consonant); i++)
			{
			temp_overlap[i] = overlap[i];
			}*/
			BackUpOrRecovery(temp_result, result, result_len + 1);
			BackUpOrRecovery(temp_overlap, overlap, ArrLen(consonant));

			result[0] = Consonant[i];
			Arrange(Consonant, consonant, vowel, result, overlap, result_len, result[0]);//���

																						 //����
																						 /*for (int i = 0; i < result_len + 1; i++)
																						 {
																						 result[i] = temp_result[i];
																						 }
																						 for (int i = 0; i < ArrLen(consonant); i++)
																						 {
																						 overlap[i] = temp_overlap[i];
																						 }*/
			BackUpOrRecovery(result, temp_result, result_len + 1);
			BackUpOrRecovery(overlap, temp_overlap, ArrLen(consonant));
			//free(temp_result);
			//free(temp_overlap);
		}
	}

	else
	{
		//�������� �ƴ϶��
		if (result[result_len - 1] == NULL)
		{
			//�������ڰ� ����
			if (!((ex_word == 'a') ||
				(ex_word == 'e') ||
				(ex_word == 'o') ||
				(ex_word == 'u') ||
				(ex_word == 'i') ||
				(ex_word == 'y') ||
				(ex_word == 'A') ||
				(ex_word == 'E') ||
				(ex_word == 'O') ||
				(ex_word == 'U') ||
				(ex_word == 'I') ||
				(ex_word == 'Y')))
			{
				//�ߺ� �˻�
				int i = 0;
				while (overlap[i] != 0)
				{
					i++;
				}
				//���� h�� �ִ´�
				if (consonant[i] == 'h')
				{
					int temp = ArrLen(result);


					//���
					int* temp_overlap = NULL;
					uint8_t* temp_result = NULL;

					temp_overlap = (int*)malloc(sizeof(int)*ArrLen(consonant));
					temp_result = (uint8_t*)malloc(sizeof(uint8_t)*(result_len + 1));

					/*for (int i = 0; i < ArrLen(consonant); i++)
					{
					temp_overlap[i] = overlap[i];
					}
					for (int i = 0; i < result_len + 1; i++)
					{
					temp_result[i] = result[i];
					}*/

					BackUpOrRecovery(temp_result, result, result_len + 1);
					BackUpOrRecovery(temp_overlap, overlap, ArrLen(consonant));
					result[temp] = consonant[i];
					overlap[i] = -1;
					Arrange(Consonant, consonant, vowel, result, overlap, result_len, result[temp]);//���

																									//����
																									/*for (int i = 0; i < ArrLen(consonant); i++)
																									{
																									overlap[i] = temp_overlap[i];
																									}
																									for (int i = 0; i < result_len + 1; i++)
																									{
																									result[i] = temp_result[i];
																									}*/
					BackUpOrRecovery(result, temp_result, result_len + 1);
					BackUpOrRecovery(overlap, temp_overlap, ArrLen(consonant));
				}
				//�ƴϸ� ������ �ִ´�
				else // ex_word ���� �����̱⶧���� ����ص� ����� ������ �ȴ�. ex_word
				{
					int temp = ArrLen(result);
					for (int i = 0; i < ArrLen(vowel); i++)
					{

						//���
						uint8_t* temp_result = NULL;
						int* temp_overlap = NULL;

						temp_result = (uint8_t*)malloc(sizeof(uint8_t)*(result_len + 1));
						temp_overlap = (int*)malloc(sizeof(int)*ArrLen(consonant));

						/*for (int i = 0; i < result_len + 1; i++)
						{
						temp_result[i] = result[i];
						}
						for (int i = 0; i < ArrLen(consonant); i++)
						{
						temp_overlap[i] = overlap[i];
						}*/
						BackUpOrRecovery(temp_result, result, result_len + 1);
						BackUpOrRecovery(temp_overlap, overlap, ArrLen(consonant));

						result[temp] = vowel[i];
						Arrange(Consonant, consonant, vowel, result, overlap, result_len, result[temp]);//���

																										//����
																										/*for (int i = 0; i < result_len + 1; i++)
																										{
																										result[i] = temp_result[i];
																										}
																										for (int i = 0; i < ArrLen(consonant); i++)
																										{
																										overlap[i] = temp_overlap[i];
																										}*/
						BackUpOrRecovery(result, temp_result, result_len + 1);
						BackUpOrRecovery(overlap, temp_overlap, ArrLen(consonant));
					}
				}
				//h�� ������ ���;���
			}
			//�������ڰ� ����
			else if ((ex_word == 'a') ||
				(ex_word == 'e') ||
				(ex_word == 'o') ||
				(ex_word == 'u') ||
				(ex_word == 'i') ||
				(ex_word == 'y') ||
				(ex_word == 'A') ||
				(ex_word == 'E') ||
				(ex_word == 'O') ||
				(ex_word == 'U') ||
				(ex_word == 'I') ||
				(ex_word == 'Y'))
			{


				int temp = ArrLen(result);
				for (int k = 0; k < ArrLen(consonant); k++)
				{
					//�ߺ� �˻�
					int i = 0;
					while (overlap[i] != 0)
					{
						i++;
					}

					//���
					int* temp_overlap = NULL;
					uint8_t* temp_result = NULL;

					temp_overlap = (int*)malloc(sizeof(int)*ArrLen(consonant));
					temp_result = (uint8_t*)malloc(sizeof(uint8_t)*(result_len + 1));

					/*for (int i = 0; i < ArrLen(consonant); i++)
					{
					temp_overlap[i] = overlap[i];
					}
					for (int i = 0; i < result_len + 1; i++)
					{
					temp_result[i] = result[i];
					}*/
					BackUpOrRecovery(temp_result, result, result_len + 1);
					BackUpOrRecovery(temp_overlap, overlap, ArrLen(consonant));

					result[temp] = consonant[i];
					overlap[i] = -1;

					Arrange(Consonant, consonant, vowel, result, overlap, result_len, result[temp]);//���

																									//����
																									/*for (int i = 0; i < ArrLen(consonant); i++)
																									{
																									overlap[i] = temp_overlap[i];
																									}
																									for (int i = 0; i < result_len + 1; i++)
																									{
																									result[i] = temp_result[i];
																									}*/
					BackUpOrRecovery(result, temp_result, result_len + 1);
					BackUpOrRecovery(overlap, temp_overlap, ArrLen(consonant));
				}

			}
		}
		//�������̶��
		else
		{
			//result[result_len] = '\n';
			//txt�� �����ϰ� ��
			//printf("%s\n", result);//debug log
			FILE* fp = fopen("nickname.txt.", "a");

			fputs((char*)result, fp);
			fputs("\n", fp);
			fclose(fp);

			//overlap_index �� ���δ� -1 �̶��
			/*int i = 0;
			while (overlap[i] != -1)
			{
			i++;
			}
			if (ArrLen(consonant) == i)
			{
			return;
			}*/
			//�ʱ�ȭ(clear)
			/*for (int i = 0; i < ArrLen(consonant); i++)
			{
			overlap_index[i] = 0;
			}
			//
			for (int i = 0; i < result_len + 1; i++)
			{
			result[i] = NULL;
			}*/
		}
	}
}

//result_split�� ���߿� ���ĺ� ������ �Ѿ�� ���� �ɷ����ִ� �Լ�
void Filter(uint8_t* result_split, uint8_t* result_untidy)
{
	int splt = 0;
	int untd = 0;
	// ���������� �Ѿ� ���� �͵� ���� ������
	while (result_split[splt] != NULL)
	{
		if (result_split[splt] >= 0x7b)
		{
			result_split[splt] -= 0x7b;
		}

		if (result_split[splt] >= 0x00 && result_split[splt] <= 0x2a)
		{
			result_split[splt] += 0x54;
		}
		else if (result_split[splt] >= 0x2b && result_split[splt] <= 0x40)
		{
			result_split[splt] += 0x2a;
		}

		if (result_split[splt] >= 0x5b && result_split[splt] <= 0x60)
		{
			result_split[splt] += 0x06;
		}
		else if (result_split[splt] >= 0x7b && result_split[splt] <= 0x7f)
		{
			result_split[splt] -= 0x05;
		}
		splt++;
	}

	splt = 0;
	while (result_split[splt] != NULL)
	{
		if ((result_split[splt] >= 0x41 && result_split[splt] <= 0x5a) ||
			(result_split[splt] >= 0x61 && result_split[splt] <= 0x7a))
		{
			result_untidy[untd] = result_split[splt];
			untd++;
		}
		splt++;
	}
	/*while (result_split[splt] != NULL)
	{
	if (!((result_split[splt] >= 0x41 && result_split[splt] <= 0x5a) ||
	(result_split[splt] >= 0x61 && result_split[splt] <= 0x7a)))
	{

	}
	//if(result_splt)
	splt++;
	}
	while (result_split[splt] != NULL)
	{
	printf("filtering..\n"); // debuglog

	if (!((result_split[splt] >= 0x41 && result_split[splt] <= 0x5a) ||
	(result_split[splt] >= 0x61 && result_split[splt] <= 0x7a)))
	{

	if (!(result_split[splt] >= 0x41) || !(result_split[splt] >= 0x61))
	{
	result_split[splt] += 0x1e;
	printf("%x\n", result_split[splt]);//debug log
	}
	else if (!(result_split[splt] <= 0x5a) || !(result_split[splt] <= 0x7a))
	{
	result_split[splt] -= 0x1e;
	printf("%x\n", result_split[splt]);//debug log
	}
	}
	if ((result_split[splt] >= 0x41 && result_split[splt] <= 0x5a) ||
	(result_split[splt] >= 0x61 && result_split[splt] <= 0x7a))
	{
	result_untidy[untd] = result_split[splt];
	untd++;
	}
	splt++;
	}*/
}

//result_combine�� ���� 1byte�� split���ִ� �Լ�
void Split(uint16_t* result_combine, uint8_t* result_split)
{
	int combine_len = ArrLen(result_combine);
	int com = 0;
	int splt = 0;

	while (result_combine[com] != NULL)
	{
		//result_combine[i] >> 8; ������Ʈ
		//result_combine[i] & 0x00ff; ������Ʈ
		if (splt % 2)//Ȧ��
		{
			result_split[splt] = result_combine[com] & 0x00ff;
			com++;
		}
		else
		{
			result_split[splt] = result_combine[com] >> 8;
		}
		splt++;
	}
}



//word�� name�� �����ִ� �Լ�
template<typename T>
void Combine(wchar_t* name, T* word, uint16_t* result_combine)
{
	int name_len, word_len = 0;
	int long_len, short_len = 0; // word�� name�� ���̰� ��� ª����

	uint16_t* short_arr = NULL;
	uint16_t* long_arr = NULL;

	name_len = ArrLen(name);
	word_len = ArrLen(word);
	//cout << "name_len : " << name_len << endl; //debug log
	//cout << "word_len : " << word_len << endl; //debug log

	if (name_len < word_len)
	{
		long_len = word_len;
		short_len = name_len;
		long_arr = (uint16_t*)word;
		short_arr = (uint16_t*)name;
	}
	else if (name_len > word_len)
	{
		long_len = name_len;
		short_len = word_len;
		long_arr = (uint16_t*)name;
		short_arr = (uint16_t*)word;
	}
	// ���̰� ���� ���
	else
	{
		long_len = name_len;
		short_len = word_len;
		long_arr = (uint16_t*)name;
		short_arr = (uint16_t*)word;
	}

	int l_i = 0, s_i = 0, r_i = 0; // long index, short index, result index
	bool first_flag = true;

	// l_i�� s_i�� 0�� ���ÿ� ó�� ���൵ �ƴ� ��� break
	while (!(l_i == 0 && s_i == 0) ||
		first_flag)
	{
		first_flag = false;
		// 8bit  0xff = 0x1111 1111
		// 16bit 0xffff = 0x1111 1111 1111 1111
		// 32bit 0xffff ffff = 0x1111 1111 1111 1111 1111 1111 1111 1111
		if ((uint16_t)long_arr[l_i] + (uint16_t)short_arr[s_i] > 0xffff)
		{
			//cout << "result_combine[r_i] > 0xffff" << endl; //debug log
			result_combine[r_i] = (uint16_t)long_arr[l_i] + (uint16_t)short_arr[s_i];
			result_combine[r_i] = ~result_combine[r_i] + 1;
			//result_combine[r_i] = result_combine[r_i] & 0x0000ffff; //32bit�ϰ�� mask
			//printf("%x\n", result_combine[r_i]); //debug log

		}
		else
		{
			//cout << "else" << endl; //debug log
			result_combine[r_i] = (uint16_t)long_arr[l_i] + (uint16_t)short_arr[s_i];
			//printf("%x\n", result_combine[r_i]);//debug log
		}

		s_i++;
		l_i++;
		r_i++;
		if (s_i == short_len)
		{
			s_i = 0;
		}
		if (l_i == long_len)
		{
			l_i = 0;
		}
	}
}

//ascii(1byte)�� �� ������ 2byte�� �о�־ �����ִ� �Լ�
void ConvertToUint16(char* word_en, uint16_t* conv_EN16bit)
{
	int len = strlen(word_en);
	//cout << len << endl; // debug log

	for (int i = 0; i < len; i++)
	{
		if (i % 2) // Ȧ�� �� ���
		{
			conv_EN16bit[i / 2] += word_en[i];
			//printf("%x ", conv_EN16bit[i / 2]);
		}
		else // ¦�� �� ���
		{
			conv_EN16bit[i / 2] = word_en[i];
			conv_EN16bit[i / 2] = conv_EN16bit[i / 2] << 8; // 8bit �̵�
															//printf("%x ", conv_EN16bit[i / 2]);
		}

	}
}

int main()
{
	setlocale(LC_ALL, "Korean");

	wchar_t name[255] = { NULL, }; // �ѱ� �̸� �Է�
	wchar_t word_kr[255] = { NULL, }; // �ܾ�(�ѱ���)
	char word_en[255] = { NULL, }; // �ܾ�(����)
	int sel_lang = 0; // language select
	int result_len = 0; // ���� �г��� ���̰� �� ����

	uint16_t conv_EN16bit[255] = { NULL, }; //�ܾ�(����)�� 8bit���� 16bit�� ��ȯ

	uint16_t result_combine[255] = { NULL, }; //�̸�+�ܾ ���� 
	uint8_t result_split[255] = { NULL, }; //result_combine�� ���� 1byte�� �и� �ؼ� ����
	uint8_t result_untidy[255] = { NULL, }; // reuslt_split�߿� ���ĺ��� ���� (�迭��������)
	uint8_t Consonant[255] = { NULL, }; // ���� �빮��
	uint8_t consonant[255] = { NULL, }; // ���� �ҹ���
	uint8_t vowel[255] = { NULL, }; // ����
	int* overlap = NULL; // consonant�� �ߺ��� �˷���
	uint8_t* result = NULL; // ���

	cout << "name?" << endl << ">>";
	wscanf(L"%ls", name);
	// printf("%x", name);

	int i = 0; // debug log �� index i
			   
			   //debug log
			   int temp = 0;
			   i = 0;

			   while (name[i] != NULL)
			   {
			   printf("X: %x\n", name[i]);
			   printf("D: %d\n", name[i]);
			   temp = (int)name[i];
			   printf("Int D : %d\n", temp);
			   i++;

			   }
			   

	cout << "0. ���� 1. �ѱ�" << endl << ">>";
	cin >> sel_lang;
	cout << "�ǹ� �ִ� �ܾ� �Է�" << endl;

	if (sel_lang)
	{
		wscanf(L"%ls", word_kr);
		/*
		// debug log

		*/
		Combine(name, word_kr, result_combine);
	}
	else
	{
		scanf("%s", word_en);
		ConvertToUint16(word_en, conv_EN16bit);

		/*
		// debug log
		cout << "conv_EN16bit : " << endl;
		int i = 0;
		while (conv_EN16bit[i] != NULL)
		{
		printf("%x | ", conv_EN16bit[i]);
		i++;
		}
		printf("\n");
		*/
		Combine(name, conv_EN16bit, result_combine);
	}

	/*
	//debug log
	cout << "result_combine : " << endl;
	int i = 0;
	while (result_combine[i] != NULL)
	{
	printf("%x | ", result_combine[i]);
	i++;
	}
	printf("\n");
	*/
	Split(result_combine, result_split);
	/*
	//debug log
	cout << "result_split : " << endl;
	i = 0;
	while (result_split[i] != NULL)
	{
	printf("%x | ", result_split[i]);
	i++;
	}
	printf("\n");
	*/
	Filter(result_split, result_untidy);
	/*
	//debug log
	cout << "result_untidy : " << endl;
	i = 0;
	while (result_untidy[i] != NULL)
	{
	printf("%c | ", result_untidy[i]);
	i++;
	}
	printf("\n");
	*/
	Division(result_untidy, Consonant, consonant, vowel);//, &Consonant_len, &consonant_len, &vowel_len);
	SelectNickNameLen(vowel, &result_len);
	/*
	//debug log
	cout << "Consonant" << endl;
	i = 0;
	while (Consonant[i] != NULL)
	{
	printf("%c | ", Consonant[i]);
	i++;
	}
	cout << endl;
	cout << "consonant" << endl;
	i = 0;
	while (consonant[i] != NULL)
	{
	printf("%c | ", consonant[i]);
	i++;
	}
	cout << endl;
	cout << "vowel" << endl;
	i = 0;
	while (vowel[i] != NULL)
	{
	printf("%c | ", vowel[i]);
	i++;
	}
	cout << endl;
	*/
	//�ߺ��˻�� ���� �ʱ�ȭ
	overlap = (int*)malloc(sizeof(int)*ArrLen(consonant));
	for (int i = 0; i < ArrLen(consonant); i++)
	{
		overlap[i] = 0;
	}

	//result_len ���̸�ŭ result ����

	result = (uint8_t*)malloc(sizeof(uint8_t)*(result_len + 1));

	for (int i = 0; i < result_len + 1; i++)
	{
		result[i] = NULL;
	}
	Arrange(Consonant, consonant, vowel, result, overlap, result_len, NULL);

	return 0;

}