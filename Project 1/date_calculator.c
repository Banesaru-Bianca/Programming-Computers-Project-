#include <stdio.h>
#include <cstdlib>

static int zile_in_luna[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool este_an_bisect(int an){
    if(an % 400 == 0){
        return true;
    }
    else if(an % 100 == 0){
        return false;
    }
    else if(an % 4 == 0){
        return true;
    }
    else{
        return false;
    }
}

int* adauga_zi(int zi, int luna, int an){
    int anul_urmator = an;
    int luna_urmatoare = luna;
    int ziua_urmatoare= zi;
    ziua_urmatoare = zi + 1;
    if( ziua_urmatoare > zile_in_luna[luna]){
        ziua_urmatoare = 1;
        luna_urmatoare = luna + 1;

        if(luna_urmatoare > 12){
            luna_urmatoare = 1;
            anul_urmator = an + 1;
            if(este_an_bisect(anul_urmator)){
                zile_in_luna[2] = 29;
            }
            else{
                zile_in_luna[2] = 28;
            }
        }
    }
    int *data_urmatoare = (int*) malloc(sizeof(int) * 3);
    *data_urmatoare = ziua_urmatoare;
    *(data_urmatoare + 1) = luna_urmatoare;
    *(data_urmatoare + 2) = anul_urmator;
    return data_urmatoare;
}

int* skip_zile(int nr_zile,int zi,int luna,int an){
    int tmp_zi = zi;
    int tmp_luna = luna;
    int tmp_an = an;
    for(int i=0;i<nr_zile;i++){
        int *data_urmatoare = adauga_zi(tmp_zi,tmp_luna,tmp_an);
        tmp_zi = data_urmatoare[0];
        tmp_luna = data_urmatoare[1];
        tmp_an = data_urmatoare[2];
    }
    int *data_finala = (int*) malloc(sizeof(int) * 3);
    *data_finala = tmp_zi;
    *(data_finala + 1) = tmp_luna;
    *(data_finala + 2) = tmp_an;
    return data_finala;
}

void print_data(int an,int luna,int zi){
    printf("\n\nData dupa 1000 de zile:\n\nAn: %d\nLuna: %d\nZi: %d\n",an,luna,zi);
}

bool validare_data(int an,int luna,int zi){

    if(este_an_bisect(an)){
        zile_in_luna[2] = 29;
    }
    else{
        zile_in_luna[2] = 28;
    }

    if((luna >= 1 && luna <= 12) && (zi >= 1 && zi <= zile_in_luna[luna])){
        return true;
    }

    else{
        return false;
    }

}


int main(){

    int zi,luna,an;

    printf("An: ");
    scanf("%d",&an);
    printf("Luna: ");
    scanf("%d",&luna);
    printf("Zi: ");
    scanf("%d",&zi);

    bool valid = validare_data(an,luna,zi);

    if(valid){
        int* data_dupa_skip = skip_zile(1000,zi,luna,an);
        int zi_skip = data_dupa_skip[0];
        int luna_skip = data_dupa_skip[1];
        int an_skip = data_dupa_skip[2];
        print_data(an_skip,luna_skip,zi_skip);
    }
    else{
        printf("Data este invalida!");
    }
    return 0;
}