#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

//파라미터
#define LEN_MIN		15	
#define LEN_MAX		50
#define STM_MIN		50	
#define STM_MAX		0
#define PRIB_MIN	10
#define PROB_MAX	90
#define AGGRO_MIN	0	
#define AGGRO_MAX	5


#define MOVE_LEFT	1
#define MOVE_STAY	0


#define ATK_NONE	0
#define ATK_CITIZEN	1
#define ATK_DONGSEOK	2


#define ACTION_REST	0
#define ACTION_PROVOKE	1
#define ACTION_PULL	2

//전역 변수 선언
int train[50];

// 상태를 나타내는 함수
void printTrain(int width, int C, int Z, int M) {
	for (int i = 0; i < width; i++) {
		if (i == 0 || i == width - 1) printf("#");
		else if (i == C)printf("C");
		else if (i == Z)printf("Z");
		else if (i == M) printf("M");
		else printf(" ");
	}
	printf("\n");
}
//시민 이동 함수
void simulate(int width, int p, int C, int Z, int citizen_aggro, int madong_aggro) {
	int r = rand() % 100;

	if (0 <= r && r <= 100 - p) {
		C--;
		(citizen_aggro)++;
	}
	else if (100 - p < r && r <= 100) {
		(citizen_aggro)--;
	}
}
//좀비 이동 함수
void simulate2(int Z, int p) {
	int l = rand() % 100;
	if (0 <= l && l <= p) {
		Z--;
	}
}
//상태 결과 함수
void printStatus(int C, int Z, int p, int citizen_aggro) {
	printf("\n");
	printf("citizen: %d -> %d (aggro: %d)\n", C + 1, C, citizen_aggro);
	printf("zonbie: %d ->%d\n", Z + 1, Z);
	printf("\n");
}
//승패 결과 함수
int checkEnd(int C, int Z, int stm) {
	if (C == 1) {
		printf("YOU WIN! \n");
		return 1;
	}
	else if (Z == (C + 1)) {
		printf("GAME OVER!\n Citizen(s) has(s) has(have) been attacked by a zombie\n");
		return 1;
	}else if(stm == 0) {
		printf("GAME OVER!\n Citizen(s) has(s) has(have) been attacked by a zombie\n");
	}
	return 0;

}
//마동석 이동 규칙 함수
int simulmadong(int M, int move, int madong_aggro) {
	if (move == 1) {
		M--;
		(madong_aggro)--;
	}
	else if (move == 0) {
		(madong_aggro)--;
	}
}

//좀비의 행동 규칙 함수
int aggro_up(int citizen_aggro, int madong_aggro, int stm) {
	if (citizen_aggro > madong_aggro) {
		printf("GAME OVER!\n, Citizen(s) has(have) been attacked by a zombie\n");
	}
	else if(madong_aggro < citizen_aggro){
		stm--;
	}
}
//마동석 행동 규칙
int madong_rule(int M, int Z, int madong_aggro, int action, int stm) {
	if (M == Z - 1) {
		
	}
}


int main(void) {

	srand(GetTickCount());

	int width, p, stm, move, citizen_aggro = 1, madong_aggro = 1, action;
	//입력
	printf("train legth(15~50)>> ");
	scanf_s("%d", &width);
	printf("madongseok stamina(0~5)>> ");
	scanf_s("%d", &stm);
	printf("percentile probability 'p' (10~90)>> ");
	scanf_s("%d", &p);
	
	int M = width - 2, Z = width - 3, C = width - 6;

	while(1) {
		//상태 출력
		for (int i = 1; i <= width; i++) {
			printf("#");
		}
		printf("\n");
		printTrain(width, C, Z, M);
		for (int i = 1; i <= width; i++) {
			printf("#");
		}
		printf("\n");
		//시민 이동
		simulate(width, p, C, Z, citizen_aggro, madong_aggro);
		//좀비 이동
		simulate2(Z, p);
		//마동석 행동 입력
		printf("madongseok move(0:stay, 1:left)>> ");
		scanf_s("%d", &move);
		//마동석 이동 규칙
		simulmadong(M, move, madong_aggro);
		if (M == Z - 1) { stm--;  }
		else if (C == Z - 1 == M - 2) { aggro_up(citizen_aggro, madong_aggro, stm); }
		//마동석 행동  규칙
		printf("madongseok action(0.rest, 1.privoke, 2. pull)>> ");
		scanf_s("%d", &action);
		if (action == 0) {
			madong_aggro--;
			stm++;
		}
		else if (action == 1) {
			madong_aggro = 5;
		}
		else if (action == 2) {
			madong_aggro += 2;
			stm--;
			int q = rand() % 100;
			if (0 <= q && q <= 100 - p) {
				printf("madongseok pulled zombie... Next turn, it can't move");
			}
			else if (100 - p < q && q <= 100) {
				printf("madongseok failed to pull zombie");
			}
		}
		//상태 결과
		printStatus(C, Z, p, citizen_aggro);
		//승패결과
		if (checkEnd(C, Z, stm)) break;
	}

	return 0;
}