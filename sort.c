# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

void BubbleSort(long int vet[], long int n){
    long int i, j, tmp, flag=0;
    for(i=0; i<n; i++){
        for(j=0;j<n-i-1;j++){
            if(vet[j]> vet[j+1]){
                flag = 1;
                tmp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = tmp;
            }
            if(flag == 0)
                break;
        }
    }
}

void InsertionSort(long int vet[], long int n){
    long int i, j, tmp;
    for(i=1;i<n;i++){
        tmp = vet[i];
        j = i-1;
        while((tmp<vet[j]) && (j>=0)){
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = tmp;
    }
}

long int Smallest(long int vet[], long int k, long int n){
    long int pos = k, small = vet[k], i;
    for(i=k+1; i<n; i++){
        if (vet[i]<small){
            small = vet[i];
            pos = i;
        }
    }
    return pos;
}

void SelectionSort(long int vet[], long int n){
    long int k, pos, tmp;
    for(k=0;k<n;k++){
        pos = Smallest(vet, k, n);
        tmp = vet[k];
        vet[k] = vet[pos];
        vet[pos] = tmp;
    }
}

long int Merge(long int vet[], long int beg, long int mid, long int end, long int size ){
    long int i = beg, j = mid+1, index = beg, tmp[size], k;
    while((i<=mid) && (j<=end)){
        if(vet[i]<vet[j]){
            tmp[index++] = vet[i++];
        }
        else{
            tmp[index++] = vet[j++];
        }
    }
    if(i<mid){
        while(j<=end){
            tmp[index++] = vet[j++];
        }
    }
    else{
        while(i<=mid){
            tmp[index++] = vet[i++];
        }
    }
    for (k=beg; k<index; k++){
        vet[k] = tmp[k];
    }
}

void MergeSort(long int vet[], long int beg, long int end, long int size){
    long int mid;
    if(beg<end){
        mid = (beg+end)/2;
        MergeSort(vet,beg,mid,size);
        MergeSort(vet, mid+1, end, size);
        Merge(vet, beg, mid, end, size);
    }
}

long int partition(long int vet[], long int beg, long int end){
    long int left, right, tmp, loc, flag = 0;
    loc = left = beg;
    right = end;
    while(flag != 1){
        while((vet[loc] <= vet[right]) && (loc != right))
            right--;
        if(loc == right) flag=1;
        else if (vet[loc]>vet[right]){
            tmp = vet[loc];
            vet[loc] = vet[right];
            vet[right] = tmp;
            loc = right;
        }
        if(flag!=1){
            while((vet[loc] >= vet[left]) && (loc!=left))
                left++;
            if(loc==left) flag=1;
            else if(vet[loc] < vet[left]){
                tmp = vet[loc];
                vet[loc] = vet[left];
                vet[left] = tmp;
                loc = left;
            }
        }
    }
    return loc;
}

void QuickSort(long int vet[], long int beg, long int end){
    long int loc;
    if(beg<end){
        loc = partition(vet, beg, end);
        QuickSort(vet, beg, loc-1);
        QuickSort(vet, loc+1, end);
    }
}


void AvgTime(int type, long int n){
    long int i;
    long int *vet = calloc(n, sizeof(long int));
    for(i=0;i<n;i++){
        vet[i] = rand() % 1000000 +1;
    }
    clock_t begin = clock();
    if (type == 0)      BubbleSort(vet, n);
    else if (type == 1) InsertionSort(vet, n);
    else if (type == 2) SelectionSort(vet, n);
    else if (type == 3) MergeSort(vet, 0, n, n);
    else if (type == 4) QuickSort(vet, 0, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) * 10000.0 / CLOCKS_PER_SEC;
    if (type == 0)
        printf("\nBubbleSort: %lf\n", time_spent);
    else if (type == 1)
        printf("\nInsertionSort: %lf\n", time_spent);
    else if(type == 2)
        printf("\nSelectionSort: %lf\n", time_spent);
    else if(type == 3)
        printf("\nMergeSort: %lf\n", time_spent);
    else if(type == 4)
        printf("\nQuickSort: %lf\n", time_spent);
    free(vet);
}

void main(){
    long int n = 10000;
    srand(time(NULL));
    AvgTime(0, n);
    AvgTime(1, n);
    AvgTime(2, n);
    AvgTime(3, n);
    AvgTime(4, n);
}

