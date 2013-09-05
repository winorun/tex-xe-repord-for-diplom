#include <iostream>
#include <stdlib.h>
#include <cmath>                    // for trigonometry functions

using namespace std;

 const double epsilon=0.001e-00;
 const double xfirst=0.5e-00;
 const double yfirst=0.5e-00;
 const double PI=3.141592e-00;
 double x;
 double y;

 double u(double x, double y)
 {
	 return double(exp(x)*exp(y));
	 //return double(sin(x)*sin(y)*sin(z));
 }
 
 double g(double x, double y)
 {
	 return double(-4.0*exp(x)*exp(y));
	// return double(-4.0*sin(x)*sin(y)*sin(z));
 }
 double phi_0(double x, double y)
 {
     return double(exp(x)*exp(y));
	// return double(sin(x)*sin(y)*sin(z));
 }
 double phi_1(double x, double y)
 {
	 return double(2.0*exp(x)*exp(y));
	// return double(-2.0*sin(x)*sin(y)*sin(z));
 }

 int boundary(double x1, double y1) // является ли точка границей
 {
	 if (x1<epsilon) {x=0.0; return 0;};
	 if (x1>(1-epsilon)) {x=1.0; return 0;};
	 if (y1<epsilon) {y=0.0; return 0;};
	 if (y1> (1-epsilon)) {y=1.0; return 0;};
	 return 1; 
	 
 }

 double min(double a, double b)
 {
	 if ( b>=a)  return a;
            else return b;
    
 }
 double diam(double x, double y) // диаметр матрицы ?
 {
	 if (x> fabs(1-x)) x= fabs(1-x);// fabs - абсолютное значение для 
									//аргумента с плавоющей точкой
	 if (y>fabs(1-y)) y=fabs(1-y); // пишем в глобальные переменные
	 return min(x,y);// возвращаем минимальное R ?
	 	 
 }
 double stat2(double a, double b, double c)
 {
      if ( c>=b) if (b>=a) return b;
               else if (a>=c) return c;
				   else return a;
     else if (c>=a) return c;
		  else if (b>=a)return a;
	            else return b;
             
}



 int main()

 {
   double N;// количество путей

   cout << "\nInput a number of ways\n";
   cin >> N;
   double U=0;
   double Disp=0;
   for (int k= 0; k<N; k++ )
   {
	   
	   
			x=xfirst;
			y=yfirst;
			
			int SN=0;
			double S=0;
			double S1=0;
			
			while (boundary(x,y))// пока не граница
		   {

			   
			   double d=diam(x,y);
			   double alpha= double (rand())/ double(RAND_MAX);// шаг ?
			   double omega1=cos(2*PI*alpha); 
			   double omega2=sin(2*PI*alpha);
			   alpha= double (rand())/ double(RAND_MAX);
			   double om1=cos(2*PI*alpha);
			   double om2=sin(2*PI*alpha);
			   int indeks=1;
			   double alpha1=0;
			   double alpha2=0;
			   while(indeks)
			   {
				   alpha1=double (rand())/ double(RAND_MAX);
				   alpha2=double (rand())/ double(RAND_MAX);
				   alpha2=4*alpha2/exp(1);
				   if (alpha2<(-4*alpha1*log(alpha1))) indeks=0;

			   }
				//cout<< "\n  "<<alpha1 <<" "<< alpha2 <<" "<< (-4*alpha1*log(alpha1));

			   double nu=alpha1*d;
			   S=S+(S1-((d*d-nu*nu-nu*nu*log(d/nu))/log(d/nu)))*d*d*g(x+nu*om1,y+nu*om2)/16;
			   SN=SN+1;
			   S1=S1-d*d;
			   x=x+omega1*d;
			   y=y+omega2*d;
			   //cout << "\n  "<<x <<" "<< y<<  ;
		   };
		   //cout << "\n boundary  "<<x <<" "<< y ;
		   S=S+(S1/4)*phi_1(x,y)+phi_0(x,y);
		   //S=S+phi_0(x,y,z);
		   cout <<"\n    "<< SN;
		   U=U+S/N;
		   Disp=Disp+(S*S)/N;
   
   
   };
   Disp=Disp-U*U;
   Disp=sqrt(fabs(Disp)/N);

   cout << "\nPresise solution   "<< u(xfirst,yfirst) ;
   cout << "\nNumerical solution    "<< U ;
   cout << "\nDelta   "<< fabs(u(xfirst,yfirst)-U) <<"\n" ;
   cout << "\nDisp   "<< Disp <<"\n" ;

	return 0;

}
