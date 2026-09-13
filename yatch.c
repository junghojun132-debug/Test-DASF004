#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE_COUNT 5
#define ROUNDS 5

// 족보 판정 및 점수 계산
int calculate_score(int dice[], int *rank)
{
    int count[7] = {0};
    int i;

    // 각 눈의 개수 계산
    for (i = 0; i < DICE_COUNT; i++) {
        count[dice[i]]++;
    }

    // 5개 모두 같음 -> 요트
    for (i = 1; i <= 6; i++) {
        if (count[i] == 5) {
            *rank = 6;
            return 50;
        }
    }

    // 스트레이트
    if ((count[1] && count[2] && count[3] && count[4] && count[5]) ||
        (count[2] && count[3] && count[4] && count[5] && count[6])) {
        *rank = 5;
        return 30;
    }

    // 풀하우스
    {
        int has3 = 0;
        int has2 = 0;

        for (i = 1; i <= 6; i++) {
            if (count[i] == 3)
                has3 = i;

            if (count[i] == 2)
                has2 = i;
        }

        if (has3 && has2) {
            *rank = 4;
            return 25;
        }
    }

    // 포카드
    for (i = 1; i <= 6; i++) {
        if (count[i] == 4) {
            *rank = 3;
            return i * 4;
        }
    }

    // 트리플
    for (i = 1; i <= 6; i++) {
        if (count[i] == 3) {
            *rank = 2;
            return i * 3;
        }
    }

    // 원페어
    for (i = 1; i <= 6; i++) {
        if (count[i] == 2) {
            *rank = 1;
            return i * 2;
        }
    }

    // 족보 없음
    *rank = 0;
    return 0;
}

// 족보 이름 출력
void print_rank(int rank)
{
    switch (rank) {
        case 6:
            printf("요트");
            break;
        case 5:
            printf("스트레이트");
            break;
        case 4:
            printf("풀하우스");
            break;
        case 3:
            printf("포카드");
            break;
        case 2:
            printf("트리플");
            break;
        case 1:
            printf("원페어");
            break;
        default:
            printf("없음");
    }
}

int main(void)
{
    int dice[DICE_COUNT];
    int total_score = 0;
    int round;
    int i;

    // 난수 초기화
    srand((unsigned int)time(NULL));

    printf("=================================\n");
    printf("       주사위 게임 - 요트\n");
    printf("=================================\n");

    for (round = 1; round <= ROUNDS; round++) {

        printf("\n[%d판]\n", round);

        // 주사위 5개 굴리기
        for (i = 0; i < DICE_COUNT; i++) {
            dice[i] = rand() % 6 + 1;
        }

        // 주사위 출력
        printf("주사위: ");
        for (i = 0; i < DICE_COUNT; i++) {
            printf("%d ", dice[i]);
        }
        printf("\n");

        // 족보 및 점수 계산
        {
            int rank;
            int score = calculate_score(dice, &rank);

            printf("족보: ");
            print_rank(rank);
            printf("\n");

            printf("점수: %d점\n", score);

            total_score += score;
            printf("현재 총점: %d점\n", total_score);
        }
    }

    printf("\n=================================\n");
    printf("          게임 종료!\n");
    printf("최종 총점: %d점\n", total_score);
    printf("=================================\n");

    return 0;
}