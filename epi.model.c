/* file sirmodess.c */
#include <R.h>
#include <math.h>
static double parms[14];
#define b1 parms[0]
#define b2 parms[1]
#define gamma parms[2]
#define rUv parms[3]
#define rLv parms[4]
#define rUc parms[5]
#define rLc parms[6]
#define rUcv parms[7]
#define rLcv parms[8]
#define epsilon parms[9]
#define alpha parms[10]
#define p parms[11]
#define omega parms[12]
#define omegav parms[13]


double betafunc (double virulence, double rU_effect, double rL_effect, double epsilon_effect) {
double result;
result = (1-epsilon_effect)*b1*pow((1-rU_effect)*(virulence-.0025),b2) + (epsilon_effect)*b1*pow((1-rL_effect)*(virulence-.0025),b2);
return result; 
}
       
/* initializer */
void initmod(void (* odeparms)(int *, double *))
{
  int N=14;
  odeparms(&N, parms);
}

/* ODEs */
void derivs (int *neq, double *t, double *y, double *ydot,double *yout, double *out, int *ip)
{

double foi;

foi = (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon) + y[5]*betafunc(alpha,rUcv,rLcv,epsilon));

/* S */
  
ydot[0] = -y[0] * foi  + y[6]*omega + y[7]*omegav + y[1]*omegav;

/* V */
  
ydot[1] =  -y[1] * (((1-rUv) * foi) + omegav);

/* I_0 */
 
ydot[2] = y[0] * foi - (gamma + alpha*p) * y[2];

/* I_V */
  
ydot[3] = y[1] * (1-rUv) * foi - (gamma + (1-rLv)*alpha*p) * y[3];

/* I_C */

ydot[4] = y[6] * (1-rUc) * foi - (gamma + (1-rLc)*alpha*p) * y[4];

/* I_C_V */

ydot[5] = y[7] * (1-rUcv) * foi - (gamma + (1-rLcv)*alpha*p) * y[5];

/* C */
  
ydot[6] = y[2]*(gamma + alpha*p) + y[4]*(gamma + (1-rLc)*alpha*p) - y[6] * (((1-rUc) * (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon)+ y[5]*betafunc(alpha,rUcv,rLcv,epsilon))) + omega);

/* C_V */

ydot[7] = y[3]*(gamma + (1-rLv)*alpha*p ) + y[5]*(gamma + (1-rLcv)*alpha*p) - y[7] * (((1-rUcv) * (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon)  + y[5]*betafunc(alpha,rUcv,rLcv,epsilon))) + omegav);


/* output for Fmat */
  
yout[0] = y[0]*betafunc(alpha,0,0,epsilon);
yout[1] = y[0]*betafunc(alpha,rUv,rLv,epsilon);
yout[2] = y[0]*betafunc(alpha,rUc,rLc,epsilon);
yout[3] = y[0]*betafunc(alpha,rUcv,rLcv,epsilon);

yout[4] = y[1]*(1-rUv)*betafunc(alpha,0,0,epsilon);
yout[5] = y[1]*(1-rUv)*betafunc(alpha,rUv,rLv,epsilon);
yout[6] = y[1]*(1-rUv)*betafunc(alpha,rUc,rLc,epsilon);
yout[7] = y[1]*(1-rUv)*betafunc(alpha,rUcv,rLcv,epsilon);

yout[8] = y[6]*(1-rUc)*betafunc(alpha,0,0,epsilon);
yout[9] = y[6]*(1-rUc)*betafunc(alpha,rUv,rLv,epsilon);
yout[10] = y[6]*(1-rUc)*betafunc(alpha,rUc,rLc,epsilon);
yout[11] = y[6]*(1-rUc)*betafunc(alpha,rUcv,rLcv,epsilon);

yout[12] = y[7]*(1-rUcv)*betafunc(alpha,0,0,epsilon);
yout[13] = y[7]*(1-rUcv)*betafunc(alpha,rUv,rLv,epsilon);
yout[14] = y[7]*(1-rUcv)*betafunc(alpha,rUc,rLc,epsilon);
yout[15] = y[7]*(1-rUcv)*betafunc(alpha,rUcv,rLcv,epsilon);

  
 /* output for Vmat */
  
yout[16] = gamma + alpha*p;
yout[17] = 0;
yout[18] = 0;
yout[19] = 0;

yout[20] = 0;
yout[21] = gamma + alpha*p*(1-rLv);
yout[22] = 0;
yout[23] = 0;

yout[24] = 0;
yout[25] = 0;
yout[26] = gamma + alpha*p*(1-rLc);
yout[27] = 0;

yout[28] = 0;
yout[29] = 0;
yout[30] = 0;
yout[31] = gamma + alpha*p*(1-rLcv);

}

/* END file mymod.c */