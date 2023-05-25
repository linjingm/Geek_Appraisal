#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ҽ��i�ĸ����,ͨ���ݹ�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n);
//���ݳ�ʼȨ�ع�����������
void huffmanTree(int w[],int huffman[][4],int n);
//Ѱ��Ȩ����С�������ڵ�
void findMin(int ii[],int huffman[][4],int n);
//��ÿ��Ҷ�ڵ���й���������
void HuffmanCode(int i,int huffman[][4],int n);
//��������char������
void inplace_swap(char *x,char *y);

int main()
{
    //��������ַ������м�¼�����ַ����ܸ���count�Լ������ַ��ĳ��ִ���arr_small[]����ͳ��
    char str[100];
    printf("Please Enter the string\n");
    scanf("%s", str);
    int arr_big[27] = {0};  //�����ַ��ĳ��ִ���
    int count = 0;  //�ַ����ܸ���
    for(int i = 0; i < strlen(str); i++)    //���������ַ����е������ַ�
    {
        for(int j = 0; j < 27; j++) //����26����д��ĸ
        {
            if(str[i] == (char)(0x41 + j))
            {
                arr_big[j] += 1;
                if(arr_big[j] == 1)
                {
                    count+=1;/*����������*/		//��¼һ�������˼�����ĸ
                }
                break;
            }
        }
    }
    printf("the letter count is %d\n",count);   //��ӡ�����ַ��������˼�����ĸ

    //ͨ��arr_big�������ַ����г��ֵ���ĸ��������ͳ�ƣ���������arr_small��
    int count2 = 0;     //�ַ����г��ֵ��ַ��ܸ���
    int arr_small[count] ;  //ͳ�������ַ�������ĸ�ĳ��ִ���
    for(int i = 0; i < 27; i++)
    {
        if(arr_big[i]!=0)/*����������*/
        {
        	
            arr_small[count2++] = arr_big[i];	/*����ע�ͣ�˵�����ã�*///�ɿ�ֵ�޳������arr��small
            
        }
    }

    //����int�Ͷ�ά���飬���鳤��[*]Ϊ���������Ľڵ����
    //c[*][0]��ŵ��Ǹýڵ��[���ڵ��λ��]��c[*][1]Ϊ�ýڵ��[�������ڵ��λ��]
    //c[*][2]��Ÿýڵ��[�������ڵ��λ��]��c[*][3]Ϊ�ýڵ��Ȩֵ
    int huffman[2 * count - 1][4];  //ǰn��ΪҶ��㣬��n-1��Ϊ�м���

    //���ݳ�ʼȨ������arr_small���ַ���������huffman��
    huffmanTree(arr_small,huffman,count);

    //����Huffman���������ܳ���WPL
    int sum = 0;
    for(int i = 0;i < count;i++)
    {
        int length = 0;
        if(huffman[i][1] == -1 && huffman[i][2] == -1) //���ý��Ϊ���һ���ӽڵ� /*�����ж�ģ��ע��*/
        {
            length = findParent(i,huffman,count);   //�õ�����Ҷ���Ĵ�Ȩ·������
            sum += arr_small[i]*length;/*����������*/  	//����Ҷ����Ȩ·�������ۼӵõ��ܳ���WPL
        }
    }
    printf("the tree's WPL  is  %d\n",sum);

    //Huffman����
    for(int i = 0;i < count;i++)
    {
        HuffmanCode(i,huffman,count);
    }

    return 0;
}

//�Ӻ�������������������
void huffmanTree(int w[],int huffman[][4],int n)
{
    //����ʼ��
    for(int i = 0; i < 2 * n - 1; i++)
    {
        huffman[i][0] = -1;
        huffman[i][1] = -1;
        huffman[i][2] = -1;
        huffman[i][3] = -1;
    }
    /*����ע�ͣ�˵�����ã�*/
    /*ÿһ��ѭ��������һ�γ�ʼ��*/ 
    for(int i = 0; i < n; i++)
    {
        huffman[i][3] = w[i];
    }
    //ÿ�γ������Ȩ����С�Ľ����кϲ���ֱ�����ղ��������
    for(int i = n; i < 2 * n - 1; i++)
    {
        int i1,i2;  //Ȩ����С���������
        int ii[2]; 
        //�ҳ�����Ȩ����С�Ľ��
        findMin(ii,huffman,n);
        i1=ii[0];
        i2=ii[1];
        //�ϲ�i1��i2���,���½����Ϣ�������ɽ��������ӽ�㣬�ӽڵ��Ӧ�ĸ���㣬�����ɽ���Ȩ�أ�
        huffman[i][1] = i1;                                   //lchild��ȡ����min�ŵ���ǰ�ڵ������� 
        huffman[i][2] = i2;                                   //rchild��ȡ����secondmin���뵱ǰ�ڵ������� 
        huffman[i1][0] = i;                                   //parent->i���±�ȡ���Ľڵ㸸�׽ڵ����� 
        huffman[i2][0] = i;                                   //parent->i���±�ȡ���Ľڵ㸸�׽ڵ�����
        huffman[i][3] = huffman[i1][3] + huffman[i2][3];      //weight ���ڵ��Ȩ�ص���������Ȩ����� 
    
    
     
		
         
        /*����������*/
        
    }
}

//�Ӻ��������ҳ�����Ȩ����С�Ľ��
void findMin(int ii[],int huffman[][4],int n)
{
    //�ҳ���һ��Ȩ����С�Ľ��
    int min = 9999999;
    int secondmin=99999999;
    for(int i = 0; i < 2 * n - 1; i++)
    {
        if(huffman[i][3] == -1 && huffman[i][0] == -1)  //�жϸý���Ƿ�Ϊ����� /*�����ж�ģ��ע�ͣ�˵�����ã�*/
        {
            break;
        }
        if(huffman[i][3] < min && huffman[i][0] == -1)  //ȷ��Ϊ���ڵ�󣬽��жԻ�����ȡȨֵ/*�����ж�ģ��ע�ͣ�˵�����ã�*/
        {
            min = huffman[i][3];
            ii[0] = i; 
        }
    }
    for(int i = 0; i < 2 * n - 1; i++)
    {
        if(huffman[i][3] == -1 && huffman[i][0] == -1)  //�ҳ��ڶ�С�Ľ�� 
        {                                               
            break;
        }
        if(huffman[i][3] < secondmin && huffman[i][0] == -1&&i!=ii[0])  
        {
            secondmin = huffman[i][3];
            ii[1] = i; 
        }
    }
    //�ҳ��ڶ���Ȩ����С�Ľ�㣨ģ���ϲ������б�д��
    
    /*����������*/
    
}

//�Ӻ����������ҽ��i�ĸ����,�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n)
{
    int length = 0;
    if(huffman[i][0] == -1)   // ���ý��Ϊ���ڵ�ʱ /*�����ж�ģ��ע��*/
    {
        return 0;
    }
    length += (findParent(huffman[i][0],huffman,n) + 1);    //ͨ���ݹ�õ���㵽����·������
    return length;
}

//�Ӻ���������ÿ��Ҷ�ڵ���й��������벢���д�ӡ
void HuffmanCode(int i,int huffman[][4],int n)
{
    char code[30];  //char����������
    int current=i;  //���嵱ǰ���ʵĽ��now
    int father = huffman[i][0]; //���嵱ǰ���ĸ��ڵ�
    int start=0;    //ÿ�α����λ�ã���ʼΪ���뵹��λ��
    int first,last;     //char�����ͷ����β��

    while(father != -1)
    {
        if(current==huffman[father][1])//�жϵ�ǰ���ĸ�����������Ƿ�Ϊ��ǰ���
		{
            code[start]='0';//�ӽ���Ǹ�����������������Ϊ0
		}
      	else
		{
      		code[start]='1';//�ӽ���Ǹ�����������������Ϊ1
	    }	
        
        current=huffman[current][0];//����˷Դ�����µ�ǰ���
        father=huffman[current][0];//ͬ������ǰ�����º󣩣����µ�ǰ���ĸ��׽��
        start++;	//���±���λ��   
        
      
        /*����������*/	   
    }
    code[start]='\0';   //���������

    //��char�����е�Ԫ��ͷβ���˽��жԵ�
    for(first = 0, last = start-1; first < last; first++,last--)
    {
        //�Ե������ڲ�Ԫ��
        inplace_swap(&code[first], &code[last]);	/*�ú������Լ���д*/
    }

    printf("%c Huffman code:  %s\n",'A'+i,code);    //��ӡ�ַ���huffman����
}

//�Ӻ���������������char�����ݣ�ʹ���˲������㣩�����Լ������ÿɶ��ԽϺõķ�������ʵ�ָĺ���
void inplace_swap(char *x,char *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}