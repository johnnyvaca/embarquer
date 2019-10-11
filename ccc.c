
#include <stdio.h>
#include <math.h>

int main()
    {
    int n = 1;
    int r = 0;
    int i = 8;

    while(n > 0)
    {
        if(n%2 == 0)
        {
            r = ((n%2)+1)*i;
        }
        else
        {
            r = ((n%2))*i;
        }


      //  if(n%2 == 0)
      //  {
      //      r = ((n%2)+1)*i;
      //  }
      //  else
      //  {
        //    r = ((n%2))*i;
       // }

       // r = (n%2)*i;
        i = i/2;
        n = (n-n%2)/2;
        printf("%d, %d\n\n",n,r);

    }
    return 0;
}