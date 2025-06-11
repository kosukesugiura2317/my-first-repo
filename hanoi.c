#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 8
#define PEGS 3

int pegs[PEGS][MAX_DISKS];   // 各棒のスタック
int heights[PEGS];           // 各棒の高さ
int num_disks;
int move_count = 0;
const char peg_names[] = {'A', 'B', 'C'};

// 描画関数
void draw_pegs() 
{
    printf("\n=== 現在の状態 ===（手数：%d）\n\n", move_count);
    for (int level = num_disks - 1; level >= 0; level--) {
        for (int p = 0; p < PEGS; p++) {
            int width = 0;
            if (level < heights[p]) {
                width = pegs[p][level];
            }

            int space = num_disks - width;
            for (int i = 0; i < space; i++) printf(" ");
            for (int i = 0; i < width; i++) printf("=");
            printf("|");
            for (int i = 0; i < width; i++) printf("=");
            for (int i = 0; i < space; i++) printf(" ");
            printf("   ");
        }
        printf("\n");
    }
    for (int p = 0; p < PEGS; p++) {
        for (int i = 0; i < num_disks; i++) printf(" ");
        printf(" %c ", peg_names[p]);
        for (int i = 0; i < num_disks; i++) printf(" ");
        printf("   ");
    }
    printf("\n\n");
}

// 終了判定（棒Cにすべてそろっている）
int is_cleared()
 {
    return heights[2] == num_disks;
}

// 入力を 0,1,2 のインデックスに変換
int peg_index(char c)
{
    for (int i = 0; i < PEGS; i++) {
        if (peg_names[i] == c) return i;
    }
    return -1;
}

// ユーザーによる1回の操作
void user_move() 
{
    char from_c, to_c;
    int from, to;

    while (1) {
        printf("移動元の棒を選んでください（A/B/C）: ");
        scanf(" %c", &from_c);
        from = peg_index(from_c);

        printf("移動先の棒を選んでください（A/B/C）: ");
        scanf(" %c", &to_c);
        to = peg_index(to_c);

        // 無効チェック
        if (from == -1 || to == -1 || from == to) {
            printf("⚠️ 無効な入力です。\n");
            continue;
        }
        if (heights[from] == 0) {
            printf("⚠️ %cにはディスクがありません。\n", peg_names[from]);
            continue;
        }
        int disk = pegs[from][heights[from] - 1];
        if (heights[to] > 0 && pegs[to][heights[to] - 1] < disk) {
            printf("⚠️ 小さいディスクの上に大きいディスクは置けません。\n");
            continue;
        }

        // 移動実行
        pegs[to][heights[to]++] = disk;
        heights[from]--;
        move_count++;
        break;
    }
}

int main() 
{
    printf("🧠 ハノイの塔 ゲームモード\n");
    printf("ディスクの数（1〜8）を入力してください：");
    scanf("%d", &num_disks);
    getchar(); // 改行読み飛ばし

    if (num_disks < 1 || num_disks > MAX_DISKS) {
        printf("⚠️ 1〜8の範囲で指定してください。\n");
        return 1;
    }

    // 初期配置：棒Aにすべてのディスク
    for (int i = 0; i < num_disks; i++) {
        pegs[0][i] = num_disks - i;
    }
    heights[0] = num_disks;

    draw_pegs();

    // ゲームループ
    while (!is_cleared()) {
        user_move();
        draw_pegs();
    }

    printf("🎉 クリア！おめでとうございます！\n");
    printf("あなたの手数：%d\n", move_count);
    printf("最小手数：%d\n", (1 << num_disks) - 1); // 2^n - 1
    return 0;
}