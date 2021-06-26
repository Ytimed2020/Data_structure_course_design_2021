/**
 * 校园安防逃生系统
 * tips:本系统以中北大学部分地区布局为例，以便形成图
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_LINE 100010
#define M 99999
#define VNUM 15

const char *a[] = {"中北医院","文体中心","龙山公园","科艺苑","快递站","龙山餐厅","文韬","唐久","主楼","八道们","大田园"
,"足球场","百业","德怀楼","一道门"};

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
}; //邻接矩阵，查找路径 

typedef struct {

 int  b[20] = {1,0,1,1,0,0,1,1,1,0,1,0,1,1,0}; //是否有消防器材
 float c[20] = {0.5,0,0.6,0.9,0,0,0.1,0.1,0.2,0,0.3,0,0.1,0.1,0}; 	
}fire_data;

typedef struct {
	int P[VNUM];           // 辅助数组
    int Dist[VNUM];       // 存放最短路径，权值
    int Mark[VNUM];		 // 标记数组
}route;

void print_all_dist(route &r,int start) {
	 if( (0 <= start) && (start < VNUM) ) {
	  	 for(int i = 0; i < VNUM; i++)         // 打印最短路径及顶点
        {
            int p = i;
            if(r.Dist[p] == 99999){
            	printf("当前没有路可寻\n\n");
			}else  printf("%s -> %s     ———距离：%d米远 ———\n\n", a[start], a[p], r.Dist[p]);  // 顶点sv到其它顶点的路径
            do
            {
                printf("%s <- ", a[p]);
                p = r.P[p];
            
            } while( p != start );
            printf("%s\n\n", a[p]);
        }	
	  }

}

//排序一下 (同时更换快排、归并等等） 
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
    int address = rand() % 14 + 1; //生成一个随即损坏地址，但是八道们和一道门我们不能损坏，所以判空一下
    printf("当前地址：%d\n",address);
    
	if(address == 9 || address == 14) {
	      printf("当前校园非常安全，躲在校园内才是最佳策略\n");      
	}else {
		//在我的想法中，这是一个损坏地址，也就是说，如果逃生窗口中包含损坏地址，我就得抛弃掉，选择去离他最远的小房间
		for(int i = 0; i < VNUM; i++) {
			int p = i;
			int flag = 0;
			if(r.Dist[p] != 99999) //如果存在这个路线我们再说 
			{
			do
            {
                if(p == address){
                	flag = 1;
                	break;
				}else  p = r.P[p];
            } while( p != start );	
                if(flag == 0) { //说明我这条路行得通
				    printf("从%s到一、八道门没有危险\n",a[i]); 
                	new_Dist[t++] = r.Dist[i];
                
				}
		    }
		} 
	    
	}
 
    
} 



void find_current_dist(route &r, int start) {
	  printf("将为您规划最优路线......分别以一道门与八道门为例子\n\n");
	  if( (0 <= start) && (start < VNUM) ) {
	  	int temp[2] = {9,14}; //一道门和八道们 
	  	for(int i = 0; i < 2; i++) {
            int p = temp[i];
            if(r.Dist[p] == 99999){
            	printf("当前没有路可寻\n\n");
			}else  printf("%s -> %s *****  距离：%d米远  *****\n\n", a[start], a[p], r.Dist[p]);  // 顶点sv到其它顶点的路径
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
			if(i != 9 && i != 14) //排除八道们和一道门 
			printf("最佳灭火器位于%s,损耗率为%.2f\n",a[i],x);	
		}
	}
} 

float best_hit_fire(fire_data f){
	//排序后返回最小值 
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
    
    if( (0 <= start) && (start < VNUM) ) //判空 
    {
        for(i = 0; i < VNUM; i++)  // 初始化辅助数组
        {
            r.Dist[i] = Matrix[start][i]; //初始化第一层 
            r.P[i] = start;       //最短路径的顶点的上一个顶点
            r.Mark[i] = 0;    //标记点 
        }

        r.Mark[start] = 1; //初始点已标记 
        
        for(i = 0; i < VNUM; i++)   //循环求得sv到某个顶点的最短路径
        {
            int min = M;                //当前离start顶点最短路径
            int index = -1;              //下个最短路径的顶点
           	
            for(j = 0; j < VNUM; j++)
            {
                if( !r.Mark[j] && (r.Dist[j] < min) )  //如果没有标记并且小于最小值 
                {
                    min = r.Dist[j];  //该点位最小值 
                    index = j; //索引过去 
                }
            }
            
            if( index > -1 )  //标记选择 
            {
                r.Mark[index] = 1;  //index可以演化为列，也就是说我第一次选择的地方，第二次从这个点走 
            }
            
            // 更新当前最短路径及顶点
            for(j = 0; j < VNUM; j++)
            {
                if( !r.Mark[j] && (min + Matrix[index][j] < r.Dist[j]) )
                {
                    r.Dist[j] = min + Matrix[index][j];
                    r.P[j] = index; //我上一次的路径 
                }
            }
        }
        
    }
}



void data_map(){
	printf("                                     ————   ————\n"); 
	printf("                                     1中北医院   2文体中心\n"); 
	printf("                                     ————   ————\n"); 
	printf("  —————       ——————      ——————         —————       ————\n"); 
	printf("   3龙山公园         4科艺苑           5快递站             6龙山餐厅        7文韬\n"); 
	printf("  —————       ——————      ——————         —————       ————\n\n"); 
	printf("  ————       ————                                                  —————\n"); 
	printf("   8唐久         9主楼                                                      10八道门\n"); 
	printf(" ————       ————                                                   —————\n"); 
	printf("                                                                 ————\n"); 
	printf("                                                                 11大田园\n"); 
	printf("                                                                 ————\n"); 
	printf("                    ————        ————\n"); 
	printf("                    12足球场         13百业\n"); 
	printf("                    ————        ————\n"); 
	printf("                      —————\n"); 
	printf("                       14德怀楼\n"); 
    printf("                      —————\n"); 
	printf("   ——————                                   \n"); 
	printf("    15一道门                                       \n"); 
	printf("   ——————                                   \n\n"); 
}

void fire_find(fire_data &f,int n){
	int find = n - 1; //找到该处
	if(f.b[find] == 1)
	printf("当前位置%s,当前存在防火器材，当前防火器材损耗率：%.2f\n",a[n],f.c[find]);
	else printf("当前位置%s.不存在防火器材\n",a[n]); 
}

void fire_modify(fire_data &f,int n,float k) {
	int find = n - 1; //我去修改某一处的防火损耗率数据
	if(f.b[find] == 1){
		f.c[find] = k;
			printf("修改成功,当前位置%s,当前存在防火器材，当前防火器材损耗率：%.2f\n",a[n],f.c[find]);
	} else {
		printf("当前位置不存在防火器材，无法修改\n");
	}
	
}


void fire_all(fire_data &f) {
    for(int i = 0; i < 15; i++) {
       if(f.b[i] == 0){
       	printf("当前位置%s.不存在防火器材\n",a[i]); 
	   }else {
	   	printf("当前位置%s,当前存在防火器材，当前防火器材损耗率：%.2f\n",a[i],f.c[i]);
	   }
	}
}


void menu(){
	printf("-----------------欢迎来到中北安防逃生系统----------------\n");
	printf("--------tips:本系统适用于校园火灾、暴力危机事件逃生使用---------\n");
	printf("-----------------功能1：校园安防地图可视化----------------\n");
	printf("-----------------功能2：安防教育----------------\n");
	printf("-----------------功能3：修改某处防火器材损耗度----------------\n");
	printf("-----------------功能4：某地防火器材损坏度查询----------------\n");
	printf("-----------------功能5：全部防火器材信息导出----------------\n");
	printf("-----------------功能6：校园逃生窗口全部路径可视化---------------\n");
	printf("-----------------功能7：校园逃生窗口最短路径查询----------------\n");
	printf("-----------------功能8：躲避火源及暴恐路线（随机生成灾害点）----------------\n");
	printf("-----------------功能9：最佳灭火器选择地点----------------\n");
	printf("----------------- 请输入您所需要查询的信息----------------\n");
}
void read_file() {
	char buf[MAX_LINE];  /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if((fp = fopen("D:\\data_map.txt","r")) == NULL)
        return;
    while(fgets(buf,MAX_LINE,fp) != NULL)
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        printf("%s\n",buf);
    }
}


int main() {
	fire_data f;
    route r;
    
    int xg,n; 
    float mod_data;
    system("title 中北安防逃生系统");
    system("color f4");
	while(1){
		menu();
		scanf("%d",&n);
		switch(n){
			case 1:
				system("cls");
				data_map();
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 2:
				system("cls");
				read_file();
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 3:
				system("cls");
				printf("请输入您要修改的位置\n");
				scanf("%d",&xg);
				printf("请输入您要修改的数值(<=1)\n");
				scanf("%f",&mod_data);
				fire_modify(f,xg,mod_data);
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 4:
			    system("cls");
				printf("请输入您要查询的位置\n");
				scanf("%d",&xg);
				fire_find(f,xg);
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 5:
				system("cls");
				fire_all(f);
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 6:
				system("cls");
				printf("请输入您当前所处位置(以序号坐标处理)\n");
				scanf("%d",&xg); 
				Dijkstra(r,xg);
				print_all_dist(r,xg);
				printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 7:
			    system("cls");
			    printf("请输入您当前所处位置(以序号坐标处理)\n");
				scanf("%d",&xg); 
				Dijkstra(r,xg);
				find_current_dist(r,xg);
			    printf("请输入回车返回菜单\n");
				system("pause");
				system("cls");
			break;
			case 8:
			    system("cls");
			    printf("请输入回车返回菜单\n");
			    Dijkstra(r,0);
			    disaster(r,0);
				system("pause");
				system("cls");
			break;
			case 9:
			    system("cls");
			    printf("请输入回车返回菜单\n");
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

