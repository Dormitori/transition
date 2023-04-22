#include <iostream>
#include <vector>
#include "bitmap_image.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void RecColor(vector<vector<int> > & m, int x, int y, int col){
    int h=m.size(), w=m[0].size();
    if (x>=w || x<0 || y<0 || y>=h) return;
    if (m[y][x]!=0) return;
    m[y][x]=col;
    RecColor(m, x+1, y, col);
    RecColor(m, x-1, y, col);
    RecColor(m, x, y+1, col);
    RecColor(m, x, y-1, col);

}

int Colorize(vector<vector<int> > & m){
    int h=m.size(), w=m[0].size();
    int col =1;
    for (int x=0; x<w; x++)
        for (int y=0; y<h; y++ )
    {
        if (m[y][x]==0){
            RecColor(m, x, y, col);
            col++;
        }
    }
    return col-2;
}

pair<double, double> UV(int x, int y, bitmap_image & BM){
    int h = BM.height();
    int w = BM.width();
    pair<double, double> res((double)x/w, (double)y/h);
    return res;
}
pair<int, int> XY(double u, double v, bitmap_image & BM){
    int h = BM.height();
    int w = BM.width();
    pair<int, int> res ((int)(w*u), (int)(h*v));
    return res;
}

void bubbleSort(double * mas, int * por)
 {
     for (int i = 0; i < 10; i++)
         for (int j = 0; j < i; j++)
             if (mas[i] < mas[j]){
                 swap(mas[i], mas[j]); // or std::swap(*i, *j);
                swap(por[i], por[j]);
             }
   // for (int i=9; i>=0; i--) cout<<por[i]<<" "<<mas[i]<<endl;
 }

int main()
{
    //rgb_t pix;
    //image.set_pixel((fib[x]+i)%1328, (fib[x]+j)%885, pix);
    //image.save_image("outp.bmp");
    srand(time(NULL));
    bitmap_image image1("images/5.bmp");
    bitmap_image image2("images/6.bmp");
    bool occ[1082][1082];
    for (int i=1; i<1081; i++)
        for (int j=1; j<1081; j++) occ[i][j]=0;
    for (int i=0; i<1082; i++) {
        occ[i][0]=1;
        occ[0][i]=1;
        occ[1081][i]=1;
        occ[i][1081]=1;
    }
    int x=1, y=1, k=1;
    int co=0;
    int t=1;
    bool flag=true;
    while(true){
        for (int i=1; i<1081&&flag; i++)
            for (int j=1; j<1081; j++){
                if (occ[i][j]==0){
                    x=i;
                    y=j;
                    flag=false;
                    break;
                }
            }
        flag=true;
        while(occ[x][y]!=1){
            rgb_t pix;
            image2.get_pixel(x-1, y-1, pix);
            image1.set_pixel(x-1, y-1, pix);
            occ[x][y]=1;
            t++;
            if (t==10000){
                image1.save_image("sequation/"+to_string(k)+".bmp");
                t=1;
                k++;
            }
            while (!(occ[x+1][y]==1&&occ[x-1][y]==1&&occ[x][y+1]==1&&occ[x][y-1]==1)){
                int direction=rand()%10;
                cout<<direction<<" ";
                if ( 4<direction&&direction<10 && occ[x+1][y]!=1) {x++; break;}
                if (direction==0 && occ[x-1][y]!=1) {x--; break;}
                if ((direction==1||direction==2) &&  occ[x][y+1]!=1) {y++; break;}
                if ((direction==3|| direction==4) && occ[x][y-1]!=1) {y--; break;}
            }
        }
    }
}
