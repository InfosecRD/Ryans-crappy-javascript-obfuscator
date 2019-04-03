#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand (time(NULL) );
    int a;
    int randVal;
    int byteCount = 0;
    int charCount = 0;
    FILE *counterPointer;
    FILE *bytePointer;
    char fileContents;
    char injectorContents;
    char contentTypeHeader[200] = "Content-Type: application/javascript";
    char pageInjector[500] = "y=document.createElement(\"script\");y.type=\"text/javascript\";y.innerHTML += \"function z() {\"";
    char pageRunner[500] = "y.innerHTML+=\"}\";document.getElementsByTagName(\"head\")[0].appendChild(y);z();while(document.scripts.length>0){document.scripts[0].remove();z = undefined;y = undefined;}";
//    printf("%s", contentTypeHeader);
    printf("%s", pageInjector);
    counterPointer = fopen(argv[1], "r");
    if (counterPointer == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    fileContents = fgetc(counterPointer);
    while (fileContents != EOF)
    {
        charCount = charCount + 1;
        fileContents = fgetc(counterPointer);
    }
    fclose(counterPointer);
    int *inputArray = malloc(sizeof(int)*charCount);
    int *offsetArray = malloc(sizeof(int)*charCount);
    int *outputArray = malloc(sizeof(int)*charCount);
    bytePointer = fopen(argv[1], "r");
    if (bytePointer == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    fileContents = fgetc(bytePointer);
    while (fileContents != EOF)
    {
        inputArray[byteCount] = fileContents;
        byteCount = byteCount + 1;
        fileContents = fgetc(bytePointer);
    }
    fclose(bytePointer);
    for (a = 0; a < charCount; a++)
    {
        offsetArray[a] = rand() % 300 + 100;
    }
    printf("\n");
    for (a = 0; a < charCount; a++)
    {
        if ( a == charCount - 1)
        {
            printf("%d];", offsetArray[a]);
        } else if ( a == 0) {
            printf("var a=[%d,", offsetArray[a]);
        } else {
            printf("%d,", offsetArray[a]);
        }
    }
    printf("\n");
    for (a = 0; a < charCount; a++)
    {
        outputArray[a] = inputArray[a] + offsetArray[a];
        if ( a == charCount - 1)
        {
            printf("%d];", outputArray[a]);
        } else if ( a == 0) {
            printf("var b=[%d,", outputArray[a]);
        } else {
            printf("%d,", outputArray[a]);
        }
    }
    printf("\n");
    printf("var c=\"\";var d=[];for(c=0;c<b.length;c++){d+=String.fromCharCode(b[c]-a[c]);};y.innerHTML+=d;var a=\"\";var b=\"\"; var c=\"\"; var d=\"\";");
    printf("\n");
    printf("%s", pageRunner);
    return 0;
}
