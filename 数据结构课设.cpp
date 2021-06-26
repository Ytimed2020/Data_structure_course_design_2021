/**
 * У԰��������ϵͳ
 * tips:��ϵͳ���б���ѧ���ֵ�������Ϊ�����Ա��γ�ͼ
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_LINE 100010
#define M 99999
#define VNUM 15

const char *a[] = {"�б�ҽԺ","��������","��ɽ��԰","����Է","���վ","��ɽ����","���","�ƾ�","��¥","�˵���","����԰"
,"����","��ҵ","�»�¥","һ����"};

int Matrix[VNUM][VNUM] = {
    {0, 15, M, 20, M,M, M, M, M, M,M, M, M, M, M},
    {M, 0, M, M, M,M, 30, M, M, M,M, M, M, M, M},
    {M, M, 0, 22, M,M, M, M, M, M,M, M, M, M, M},
    {M, M, M, 0, 22,M, M, M, M, M,M, M, M, M, M},
    {M, M, M, M, 0,22, M, M, M, M,M, M, M, M, M},
    {M, M, M, M, M,0, 23, M, M, M,M, M, M, M, M},
    {M, M, M, M, M,M, 0, M, M, 19,M, M, M, M, M},
    {M, M, M, M, M,M, M, 0, 22, M,M, M, M, M, M},
    {M, M, M, M, M,M, M, M, 0, M,M, M, 45, M, M},
    {M, M, M, M, M,M, M, M, M, 0,8, M, M, M, M},
    {M, M, M, M, M,M, M, M, M, M,0, M, M, 55, M},
    {M, M, M, M, M,M, M, M, M, M,M, 0, 20, M, 40},
    {M, M, M, M, M,M, M, M, M, M,M, M, 0, M, M},
    {M, M, M, M, M,M, M, M, M, M,M, M, M, 0, 30},
    {M, M, M, M, M,M, M, M, M, M,M, M, M, M, 0},
}; //�ڽӾ��󣬲���·�� 

typedef struct {

 int  b[20] = {1,0,1,1,0,0,1,1,1,0,1,0,1,1,0}; //�Ƿ�����������
 float c[20] = {0.5,0,0.6,0.9,0,0,0.1,0.1,0.2,0,0.3,0,0.1,0.1,0}; 	
}fire_data;

typedef struct {
	int P[VNUM];           // ��������
    int Dist[VNUM];       // ������·����Ȩֵ
    int Mark[VNUM];		 // �������
}route;

void print_all_dist(route &r,int start) {
	 if( (0 <= start) && (start < VNUM) ) {
	  	 for(int i = 0; i < VNUM; i++)         // ��ӡ���·��������
        {
            int p = i;
            if(r.Dist[p] == 99999){
            	printf("��ǰû��·��Ѱ\n\n");
			}else  printf("%s -> %s     ���������룺%d��Զ ������\n\n", a[start], a[p], r.Dist[p]);  // ����sv�����������·��
            do
            {
                printf("%s <- ", a[p]);
                p = r.P[p];
            
            } while( p != start );
            printf("%s\n\n", a[p]);
        }	
	  }

}

//����һ�� (ͬʱ�������š��鲢�ȵȣ� 
int Bubble(route &r, int q[], int is) {
	int str = sizeof(q)/sizeof(q[0]);
	printf("%d",str);
	for(int i = 0; i < str - 1; i++) 
		for(int j = i; j < str - 1; j++)
		   if(q[j] >= q[j + 1]) {
		   	  int temp = q[j];
		   	  q[j] = q[j + 1];
		   	  q[j + 1] = temp;
		   }
	printf("%d",str);

	
	if(is == 0) {
		return q[str-1];
	}else return q[0];
    
}

void disaster(route &r, int start) {
	int new_Dist[VNUM];
	memset(new_Dist,0,15); 
	int t = 0; 
    int address = rand() % 14 + 1; //����һ���漴�𻵵�ַ�����ǰ˵��Ǻ�һ�������ǲ����𻵣������п�һ��
    printf("��ǰ��ַ��%d\n",address);
    
	if(address == 9 || address == 14) {
	      printf("��ǰУ԰�ǳ���ȫ������У԰�ڲ�����Ѳ���\n");      
	}else {
		//���ҵ��뷨�У�����һ���𻵵�ַ��Ҳ����˵��������������а����𻵵�ַ���Ҿ͵���������ѡ��ȥ������Զ��С����
		for(int i = 0; i < VNUM; i++) {
			int p = i;
			int flag = 0;
			if(r.Dist[p] != 99999) //����������·��������˵ 
			{
			do
            {
                if(p == address){
                	flag = 1;
                	break;
				}else  p = r.P[p];
            } while( p != start );	
                if(flag == 0) { //˵��������·�е�ͨ
				    printf("��%s��һ���˵���û��Σ��\n",a[i]); 
                	new_Dist[t++] = r.Dist[i];
                
				}
		    }
		} 
	    
	}
 
    
} 



void find_current_dist(route &r, int start) {
	  printf("��Ϊ���滮����·��......�ֱ���һ������˵���Ϊ����\n\n");
	  if( (0 <= start) && (start < VNUM) ) {
	  	int temp[2] = {9,14}; //һ���źͰ˵��� 
	  	for(int i = 0; i < 2; i++) {
            int p = temp[i];
            if(r.Dist[p] == 99999){
            	printf("��ǰû��·��Ѱ\n\n");
			}else  printf("%s -> %s *****  ���룺%d��Զ  *****\n\n", a[start], a[p], r.Dist[p]);  // ����sv�����������·��
		    do
            {
                printf("%s <- ", a[p]);
                p = r.P[p];
            
            } while( p != start );
            printf("%s\n\n", a[p]);	
        }
	  }
}

int find_home(fire_data f,int x){
	for(int i = VNUM - 1; i >= 0; i--)
	{
		if(x == f.c[i]){
			if(i != 9 && i != 14) //�ų��˵��Ǻ�һ���� 
			printf("��������λ��%s,�����Ϊ%.2f\n",a[i],x);	
		}
	}
} 

float best_hit_fire(fire_data f){
	//����󷵻���Сֵ 
	for(int i = 0; i < VNUM - 1; i++) 
		for(int j = i; j < VNUM - 1; j++)
		   if(f.c[j] >= f.c[j + 1]) {
		   	  int temp = f.c[j];
		   	  f.c[j] = f.c[j + 1];
		   	  f.c[j + 1] = temp;
		   }	   

     return f.c[0];
} 

void Dijkstra(route &r,int start) {
    int i = 0;
    int j = 0;
    
    if( (0 <= start) && (start < VNUM) ) //�п� 
    {
        for(i = 0; i < VNUM; i++)  // ��ʼ����������
        {
            r.Dist[i] = Matrix[start][i]; //��ʼ����һ�� 
            r.P[i] = start;       //���·���Ķ������һ������
            r.Mark[i] = 0;    //��ǵ� 
        }

        r.Mark[start] = 1; //��ʼ���ѱ�� 
        
        for(i = 0; i < VNUM; i++)   //ѭ�����sv��ĳ����������·��
        {
            int min = M;                //��ǰ��start�������·��
            int index = -1;              //�¸����·���Ķ���
           	
            for(j = 0; j < VNUM; j++)
            {
                if( !r.Mark[j] && (r.Dist[j] < min) )  //���û�б�ǲ���С����Сֵ 
                {
                    min = r.Dist[j];  //�õ�λ��Сֵ 
                    index = j; //������ȥ 
                }
            }
            
            if( index > -1 )  //���ѡ�� 
            {
                r.Mark[index] = 1;  //index�����ݻ�Ϊ�У�Ҳ����˵�ҵ�һ��ѡ��ĵط����ڶ��δ�������� 
            }
            
            // ���µ�ǰ���·��������
            for(j = 0; j < VNUM; j++)
            {
                if( !r.Mark[j] && (min + Matrix[index][j] < r.Dist[j]) )
                {
                    r.Dist[j] = min + Matrix[index][j];
                    r.P[j] = index; //����һ�ε�·�� 
                }
            }
        }
        
    }
}



void data_map(){
	printf("                                     ��������   ��������\n"); 
	printf("                                     1�б�ҽԺ   2��������\n"); 
	printf("                                     ��������   ��������\n"); 
	printf("  ����������       ������������      ������������         ����������       ��������\n"); 
	printf("   3��ɽ��԰         4����Է           5���վ             6��ɽ����        7���\n"); 
	printf("  ����������       ������������      ������������         ����������       ��������\n\n"); 
	printf("  ��������       ��������                                                  ����������\n"); 
	printf("   8�ƾ�         9��¥                                                      10�˵���\n"); 
	printf(" ��������       ��������                                                   ����������\n"); 
	printf("                                                                 ��������\n"); 
	printf("                                                                 11����԰\n"); 
	printf("                                                                 ��������\n"); 
	printf("                    ��������        ��������\n"); 
	printf("                    12����         13��ҵ\n"); 
	printf("                    ��������        ��������\n"); 
	printf("                      ����������\n"); 
	printf("                       14�»�¥\n"); 
    printf("                      ����������\n"); 
	printf("   ������������                                   \n"); 
	printf("    15һ����                                       \n"); 
	printf("   ������������                                   \n\n"); 
}

void fire_find(fire_data &f,int n){
	int find = n - 1; //�ҵ��ô�
	if(f.b[find] == 1)
	printf("��ǰλ��%s,��ǰ���ڷ������ģ���ǰ������������ʣ�%.2f\n",a[n],f.c[find]);
	else printf("��ǰλ��%s.�����ڷ�������\n",a[n]); 
}

void fire_modify(fire_data &f,int n,float k) {
	int find = n - 1; //��ȥ�޸�ĳһ���ķ������������
	if(f.b[find] == 1){
		f.c[find] = k;
			printf("�޸ĳɹ�,��ǰλ��%s,��ǰ���ڷ������ģ���ǰ������������ʣ�%.2f\n",a[n],f.c[find]);
	} else {
		printf("��ǰλ�ò����ڷ������ģ��޷��޸�\n");
	}
	
}


void fire_all(fire_data &f) {
    for(int i = 0; i < 15; i++) {
       if(f.b[i] == 0){
       	printf("��ǰλ��%s.�����ڷ�������\n",a[i]); 
	   }else {
	   	printf("��ǰλ��%s,��ǰ���ڷ������ģ���ǰ������������ʣ�%.2f\n",a[i],f.c[i]);
	   }
	}
}


void menu(){
	printf("-----------------��ӭ�����б���������ϵͳ----------------\n");
	printf("--------tips:��ϵͳ������У԰���֡�����Σ���¼�����ʹ��---------\n");
	printf("-----------------����1��У԰������ͼ���ӻ�----------------\n");
	printf("-----------------����2����������----------------\n");
	printf("-----------------����3���޸�ĳ������������Ķ�----------------\n");
	printf("-----------------����4��ĳ�ط��������𻵶Ȳ�ѯ----------------\n");
	printf("-----------------����5��ȫ������������Ϣ����----------------\n");
	printf("-----------------����6��У԰��������ȫ��·�����ӻ�---------------\n");
	printf("-----------------����7��У԰�����������·����ѯ----------------\n");
	printf("-----------------����8����ܻ�Դ������·�ߣ���������ֺ��㣩----------------\n");
	printf("-----------------����9����������ѡ��ص�----------------\n");
	printf("----------------- ������������Ҫ��ѯ����Ϣ----------------\n");
}
void read_file() {
	char buf[MAX_LINE];  /*������*/
    FILE *fp;            /*�ļ�ָ��*/
    int len;             /*���ַ�����*/
    if((fp = fopen("D:\\data_map.txt","r")) == NULL)
        return;
    while(fgets(buf,MAX_LINE,fp) != NULL)
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*ȥ�����з�*/
        printf("%s\n",buf);
    }
}


int main() {
	fire_data f;
    route r;
    
    int xg,n; 
    float mod_data;
    system("title �б���������ϵͳ");
    system("color f4");
	while(1){
		menu();
		scanf("%d",&n);
		switch(n){
			case 1:
				system("cls");
				data_map();
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 2:
				system("cls");
				read_file();
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 3:
				system("cls");
				printf("��������Ҫ�޸ĵ�λ��\n");
				scanf("%d",&xg);
				printf("��������Ҫ�޸ĵ���ֵ(<=1)\n");
				scanf("%f",&mod_data);
				fire_modify(f,xg,mod_data);
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 4:
			    system("cls");
				printf("��������Ҫ��ѯ��λ��\n");
				scanf("%d",&xg);
				fire_find(f,xg);
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 5:
				system("cls");
				fire_all(f);
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 6:
				system("cls");
				printf("����������ǰ����λ��(��������괦��)\n");
				scanf("%d",&xg); 
				Dijkstra(r,xg);
				print_all_dist(r,xg);
				printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 7:
			    system("cls");
			    printf("����������ǰ����λ��(��������괦��)\n");
				scanf("%d",&xg); 
				Dijkstra(r,xg);
				find_current_dist(r,xg);
			    printf("������س����ز˵�\n");
				system("pause");
				system("cls");
			break;
			case 8:
			    system("cls");
			    printf("������س����ز˵�\n");
			    Dijkstra(r,0);
			    disaster(r,0);
				system("pause");
				system("cls");
			break;
			case 9:
			    system("cls");
			    printf("������س����ز˵�\n");
			    Dijkstra(r,0);
			    float temps = best_hit_fire(f);
			    find_home(f,temps);
				system("pause");
				system("cls");
			break;	
			
		}
	} 
    return 0;
}

