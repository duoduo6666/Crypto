unsigned long str_len(char str[]){
    unsigned long i = 0;
    char ASCII = 0xFF;
    while (ASCII != 0)
    {
        i++;
        ASCII = str[i];
    }
    return i;
}

char str_cmp(char str0[],char str1[]){
    unsigned long i = 0;
    while (str0[i] == str1[i]){   
        if ((str0[i] | str1[i]) == 0){return 1;}
        i++;
    }
    return 0;
}