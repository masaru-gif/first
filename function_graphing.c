// Created 2022.7.24
// Memo 使える文字 x 演算子 + - * /
// ターミナルで画面サイズ最大で出力して欲しいです。
// 半角入力でお願いします。
// 例: -1000/x, x*x-20*x+110, x, -x などがわかりやすいです。
// sg などの入力も試してもらえると嬉しいです。
// 希望通りの入力じゃないとバグります。

#include <stdio.h>
#include <stdbool.h>

int f(int,char[],int);

int main(void)
{
    int x_max = 100, y_max = 35; // 設定変数初期値
    int x_min = -100, y_min = -35, scale = 1;

    int y, x, n = 0, i = 1;
    char ch[100][100] = {'\0'}; // fn(x)の数(ch[n][100]);
    bool ast = false;

    while(ch[n][0] != 'f') // 終了or実行
    {
        printf("初期化: r 終了: f\n");
        printf("設定: sr 初期値, ss 倍率, sg サイズ\n");

        if(ch[n][0] == 'r') // リセット
        {
            n = 0;
            char ch[100][100] = {'\0'};
        }

        for(y = y_max; y >= y_min; y--) // グラフ
        {
            for(x = x_min; x <= x_max; x++)
            {
                for(int i = 1;i <= n; i++)if(f(x,ch[i],scale) == y)ast = true;
                if(ast == true)
                {
                    if(n == 0)putchar('-');
                    else putchar('*');
                    ast = false;
                }
                else if(y == 0)putchar('-');
                else if(x == 0)putchar('|');
                else putchar(' ');
            }
            printf("\n");
        }
        printf("f%d(x) = ",n+1);
        n++;
        scanf("%s",ch[n]);

        if(ch[n][0] == 's') // 設定
        {
            printf("-----設定-----\n");
            if(ch[n][1] == 's') // 倍率
            {
                printf("現在: 倍率 = f(x)/%d\n",scale);
                printf("変更: 倍率 = f(x)/");
                scanf("%d",&scale);
            }
            while(ch[n][1] == 'g') // グラフサイズ
            {
                printf("現在： max(x,y) = %d,%d\n",x_max,y_max);
                printf("      min(x,y) = %d,%d\n",x_min,y_min);
                printf("変更： max(x,y) = ");
                scanf("%d,%d",&x_max,&y_max);
                printf("      min(x,y) = ");
                scanf("%d,%d",&x_min,&y_min);
                if(x_max >= 0 && 0 >= x_min && y_max >= 0 && 0 >= y_min)break;
                printf("***このサイズには対応しておりません。***\n");
            }
            if(ch[n][1] == 'r') // 初期値に戻す
            {
                x_max = 100, y_max = 35; // 設定変数初期値
                x_min = -100, y_min = -35, scale = 1;
            }
            n--;
        }
    }
    return 0;
}

//関数計算
int f(int x,char ch[],int scale)
{
    int fx = 0, item[30] = {0}, operator = 0, num = 0, p = 0, itemnum = 1;
    bool nummemory = false, minus = false;

    for(int k = 0; k < 100; k++)
    {
        // 数字
        if(48 <= (int)ch[k] && (int)ch[k] <= 57)
        {    
            num += (int)ch[k] - 48;
            nummemory = true;
            if(ch[k-1] == '-')minus = true;
            if(48 <= (int)ch[k+1] && (int)ch[k+1] <= 57)num *= 10;
            if((int)ch[k+1] < 48 || 57 < (int)ch[k+1])
            {
                nummemory = false;
                p = 0;
                if(minus == true)
                {
                    num *= -1;
                    minus = false;
                }

                switch(operator)
                {
                    case 3:
                        item[itemnum] *= num;
                        operator = 0;
                        break;
                    case 4:
                        item[itemnum] /= num;
                        operator = 0;
                        break;
                    default:
                        item[itemnum] += num;
                        break;
                }
                num = 0;
            }   
        }

        // X!!!
        if(ch[k] == 'x')
        {
                switch(operator)
                {
                    case 1:
                        item[itemnum] += x;
                        operator = 0;
                        break;
                    case 2:
                        item[itemnum] -= x;
                        operator = 0;
                        break;
                    case 3:
                        item[itemnum] *= x;
                        operator = 0;
                        break;
                    case 4:
                        item[itemnum] /= x;
                        operator = 0;
                        break;
                    default:
                        item[itemnum] += x;
                        break;
                }
        }

        // 演算子
        else
        {
            switch (ch[k])
            {
                case '+':
                    operator = 1;
                    itemnum++;
                    break;
                case '-':
                    operator = 2;
                    if(k != 0)itemnum++;
                    break;
                case '*':
                    operator = 3;
                    break;
                case '/':
                    operator = 4;
                    break;
                default:
                    break;
            }
        }
    }
    for(int i = 1; i <= itemnum; i++)fx += item[i];
    return (fx/scale);
}