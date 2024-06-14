#include <stdio.h>
#include <stdlib.h>

typedef struct t_shape{
    int x[4];
    int y[4];
    int n;
    float area;
    struct t_shape *next;
} shape;

shape *read(char *filename);
void calc_areas(shape *l);
void print(shape *l);
void free_list(shape *l);
shape *merge_and_sort(shape *l1, shape *l2);
void equal_two_shapes(shape *s1, shape *s2);

int main(){
    shape *list;
    shape *list2;

    list = read("shapes1.txt");
    list2 = read("shapes2.txt");
    calc_areas(list);
    calc_areas(list2);

    //print(list);

    shape *merged = merge_and_sort(list, list2);
    print(merged);

    free_list(list);
    return 0;
}

shape *merge_and_sort(shape *l1, shape *l2){
    shape *newHead = NULL;
    shape *prev = NULL;
    shape *tmp1 = l1;
    shape *tmp2 = l2;

    while (tmp1 != NULL){
        shape *tmp = (shape *)malloc(sizeof(shape));
        if (newHead == NULL){
            newHead = tmp;
            equal_two_shapes(tmp, tmp1);
            prev = tmp;
        } else {
            prev->next = tmp;
            equal_two_shapes(tmp, tmp1);
            prev = tmp;
        }
        tmp1 = tmp1->next;
    }


    while (tmp2 != NULL){
        shape *tmp = (shape *)malloc(sizeof(shape));
        if (newHead == NULL){
            newHead = tmp;
            equal_two_shapes(tmp, tmp2);
            prev = tmp;
        } else {
            prev->next = tmp;
            equal_two_shapes(tmp, tmp2);
            prev = tmp;
        }
        tmp2 = tmp2->next;
    }

    shape *tmp = newHead;
    shape *tmpiter = newHead->next;

    while (tmp != NULL){
        tmpiter = tmp->next;
        while (tmpiter != NULL){
            if (tmp->area > tmpiter->area){
                shape *tmpshape = (shape *)malloc(sizeof(shape));
                equal_two_shapes(tmpshape, tmp);
                equal_two_shapes(tmp, tmpiter);
                equal_two_shapes(tmpiter, tmpshape);
            }
            tmpiter = tmpiter->next;
        }
        tmp = tmp->next;
    }
    return newHead;
}

void equal_two_shapes(shape *s1, shape *s2){
    s1->n = s2->n;
    for (int i = 0; i < s2->n; i++){
        s1->x[i] = s2->x[i];
        s1->y[i] = s2->y[i];
    }
    s1->area = s2->area;
}

void free_list(shape *l){
    shape *tmp;
    while (l != NULL){
        tmp = l;
        l = l->next;
        free(tmp);
    }
}

void print(shape *l){
    shape *tmp = l;
    int i = 1;
    if (l == NULL){
        return;
    }
    while (tmp != NULL){
        if (tmp->n == 3){
            printf("%d. Triangle: (%d, %d), (%d, %d), (%d, %d), Area: %1.f\n", i, tmp->x[0], tmp->y[0], tmp->x[1], tmp->y[1], tmp->x[2], tmp->y[2], tmp->area);
        } else {
            printf("%d. Rectangle: (%d, %d), (%d, %d), (%d, %d), (%d, %d), Area: %1.f\n", i, tmp->x[0], tmp->y[0], tmp->x[1], tmp->y[1], tmp->x[2], tmp->y[2], tmp->x[3], tmp->y[3], tmp->area);
        }
        tmp = tmp->next;
        i++;
    }
}

float myabs(float a){
    if (a < 0){
        return -a;
    }
    return a;
}

void calc_areas(shape *l){
    shape *tmp = l;
    if (l == NULL){
        return;
    }
    while (tmp != NULL){
        if (tmp->n == 3){
            tmp->area = myabs((tmp->x[0] * (tmp->y[1] - tmp->y[2]) + tmp->x[1] * (tmp->y[2] - tmp->y[0]) + tmp->x[2] * (tmp->y[0] - tmp->y[1])) / 2.0f);
        } else {
            tmp->area = myabs((tmp->x[0] * tmp->y[1] + tmp->x[1] * tmp->y[2] + tmp->x[2] * tmp->y[3] + tmp->x[3] * tmp->y[0] - tmp->x[1] * tmp->y[0] - tmp->x[2] * tmp->y[1] - tmp->x[3] * tmp->y[2] - tmp->x[0] * tmp->y[3]) / 2.0f);
        }
        tmp = tmp->next;
    }
}

shape *read(char *filename){
    FILE *fp;
    char line[100];
    shape *head;
    shape *tmp;
    shape *prev;

    head = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found\n");
        exit(1);
    }

    while (fgets(line, 100, fp) != NULL){
        char type;
        char dummy;
        int dummy2;
        tmp = (shape *)malloc(sizeof(shape));
        if (line[0] == 't'){
            sscanf(line, "%c%c%d,%d,%d,%d", &type, &dummy, &dummy2, &(tmp->x[0]), &(tmp->x[1]), &(tmp->x[2]));
            fgets(line, 100, fp);
            sscanf(line, "%c%c%d,%d,%d,%d", &type, &dummy, &dummy2, &(tmp->y[0]), &(tmp->y[1]), &(tmp->y[2]));
            tmp->n = 3;
        }
        else {
            sscanf(line, "%c%c%d,%d,%d,%d,%d", &type, &dummy, &dummy2, &(tmp->x[0]), &(tmp->x[1]), &(tmp->x[2]), &(tmp->x[3]));
            tmp->n = 4;
            fgets(line, 100, fp);
            sscanf(line, "%c%c%d,%d,%d,%d,%d", &type, &dummy, &dummy2, &(tmp->y[0]), &(tmp->y[1]), &(tmp->y[2]), &(tmp->y[3]));
        }
        if (head == NULL){
            head = tmp;
            prev = tmp;
        } else {
            prev->next = tmp;
            prev = tmp;
        }
    }
    prev->next = NULL;
    fclose(fp);
    return head;
}