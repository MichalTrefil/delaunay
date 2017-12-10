#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "delaunay.h"

void swapp (double *px, double *py)

{
    double tmp = *px;
    *px = *py;
    *py = tmp;
}


int main()
{
    clock_t start = clock();
    FILE * fp;
    FILE * fp2;
    FILE * log;

    double nasobek, offset,h,h_ideal;
    int pocet_pointu_v_souboru,i,j = 0;
    char buf [50];
    delaunay2d_t* d;
    tri_delaunay2d_t* t;
    del_point2d_t b[1000];
    /// /////////////////////////////////////////////////////////////////
    log = fopen ("log_delaunay.txt", "a");
    fprintf(log,"\n************************************************\n");
    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    fprintf(log,"Cas logu: %s", c_time_string);

    fp = fopen ("points_for_delaunay.txt", "r");
    fgets(buf, sizeof buf, fp);
    sscanf(buf, "%d %lf %lf", &pocet_pointu_v_souboru,&nasobek,&offset);
    fprintf(log,"Pocet pointu: %d \nnasobek: %.1f offset: %.1f\n",pocet_pointu_v_souboru,nasobek,offset);
    /////////////////////////////////////////////////////////////////////////////
    i = 0;
    while (fgets(buf, sizeof buf, fp) != NULL)
    {
        sscanf(buf, "%lf:%lf:%lf", &b[i].x,&b[i].y,&b[i].z);
        i++;
    }
    fclose(fp);

    /// //////////////////////////////////////////////////////
    /// //////////////////////////////////////////////////////
    d =  delaunay2d_from(b,pocet_pointu_v_souboru);/// ///////
    t =  tri_delaunay2d_from(d);                   /// ///////
    /// //////////////////////////////////////////////////////
    /// //////////////////////////////////////////////////////

    ///posun a offset v ose z
    for(i=0; i<pocet_pointu_v_souboru; i++)
    {
        b[i].z = b[i].z * nasobek;
        b[i].z = b[i].z + offset;
    }
    /// hlavicka
    fp2 = fopen ("triangle_from_delaunay.txt", "w");
    fprintf(log,"Pocet trianglu: %d\n",t->num_triangles);
    fprintf(fp2,"%d\n",t->num_triangles);

    j = 0;

    /// ulozeni dat do souboru
    for(i = 0; i < t->num_triangles ; i++)
    {

        double b0x = b[t->tris[j+0]].x;
        double b0y = b[t->tris[j+0]].y;
        double b0z = b[t->tris[j+0]].z;
        double b1x = b[t->tris[j+1]].x;
        double b1y = b[t->tris[j+1]].y;
        double b1z = b[t->tris[j+1]].z;
        double b2x = b[t->tris[j+2]].x;
        double b2y = b[t->tris[j+2]].y;
        double b2z = b[t->tris[j+2]].z;

        /// trojuhelnik body
        fprintf(fp2," %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f",\
                b0x, b0y, b0z, b1x, b1y, b1z, b2x, b2y, b2z );
        /// trojuhelnik delky stran nedulezite, pokus o zobrazeni kvality
        ///rezervovano/////////////////////////////////////////////////////////////

        double a, a_z;
        double b, b_z;
        double c, c_z, h_z;




        a = sqrt((b0x - b1x)*(b0x - b1x) + (b0y - b1y)*(b0y - b1y) + (b0z - b1z)*(b0z - b1z));
        b = sqrt((b2x - b1x)*(b2x - b1x) + (b2y - b1y)*(b2y - b1y) + (b2z - b1z)*(b2z - b1z));
        c = sqrt((b2x - b0x)*(b2x - b0x) + (b2y - b0y)*(b2y - b0y) + (b2z - b0z)*(b2z - b0z));

        a_z = sqrt((b0x - b1x)*(b0x - b1x) + (b0y - b1y)*(b0y - b1y) );
        b_z = sqrt((b2x - b1x)*(b2x - b1x) + (b2y - b1y)*(b2y - b1y) );
        c_z = sqrt((b2x - b0x)*(b2x - b0x) + (b2y - b0y)*(b2y - b0y) );



        ///obsah z idealni pohled
        h = (a+b+c)/2;
        h = sqrt(h*(h-a)*(h-b)*(h-c));

        ///obsah z pohledu Z
        h_z = (a_z+b_z+c_z)/2;
        h_z = sqrt(h_z*(h_z-a_z)*(h_z-b_z)*(h_z-c_z));

        ///obsah podle nejdelsi strany
        /// a = MAX b = STRED c = MIN

        if (a<b) swapp(&a,&b);
        if (a<c) swapp(&a,&c);
        if (b<c) swapp(&b,&c);

        h_ideal = (a+a+a)/2;
        h_ideal = sqrt(h_ideal*(h_ideal-a)*(h_ideal-a)*(h_ideal-a));



        fprintf (fp2," %.2f %.2f -1: -1\n", h_ideal/h, h/h_z);
        ////////////////////////////////////////////////////////////////////////////////////
        j = j + 3;
    }
    fclose(fp2);
    fprintf(log,"Cas programu : %.1f msec\n",(float)(clock() - start));
    fclose(log);

    return 0;
}
