#include <stdio.h>
#include <string.h>

#define MAX_SCHOOLS 5
#define MAX_LINE_LENGTH 50

typedef struct {
    int male_score;
    int female_score;
} SchoolScores;

int main() {
    // 创建一个数组来存储每个学校的成绩
    SchoolScores schools[MAX_SCHOOLS] = {{0}};
    char line[MAX_LINE_LENGTH];
    char event[20], gender, school[20];
    int score;
    // 处理输入数据并计算各学校的成绩
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        sscanf(line, "%s %c %s %d", event, &gender, school, &score);
        if (gender == 'M')
            schools[school[0] - 'A'].male_score += score;
        else if (gender == 'F')
            schools[school[0] - 'A'].female_score += score;
    }
    // 输出结果
    for (int i = 0; i < MAX_SCHOOLS; i++) {
        if (schools[i].male_score != 0) // 只输出有成绩的学校
            printf("%c M %d\n", 'A' + i, schools[i].male_score);
        if (schools[i].female_score != 0) // 只输出有成绩的学校
            printf("%c F %d\n", 'A' + i, schools[i].female_score);
        if(schools[i].male_score+schools[i].female_score != 0)
            printf("%c %d\n",'A'+i,schools[i].male_score+schools[i].female_score);
    }
    return 0;
}