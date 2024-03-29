/* file sirmodess.c */
#include <R.h>
#include <math.h>
static double parms[15];
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
#define q parms[14]


double betafunc (double virulence, double rU_effect, double rL_effect, double epsilon_effect) {
double result;
result = (1-epsilon_effect)*b1*pow((1-rU_effect)*(virulence-.0025),b2) + (epsilon_effect)*b1*pow((1-rL_effect)*(virulence-.0025),b2);
return result; 
}
       
/* initializer */
void initmod(void (* odeparms)(int *, double *))
{
  int N=15;
  odeparms(&N, parms);
}

/* ODEs */
void derivs (int *neq, double *t, double *y, double *ydot,double *yout, double *out, int *ip)
{

double foi;

foi = (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon) + y[5]*betafunc(alpha,rUcv,rLcv,epsilon));

/* S */
  
ydot[0] = -y[0] * foi  + y[8]*omega + y[9]*omegav + y[1]*omegav;

if( (y[0] < 0.0000000001) && (ydot[0] < 0)) {ydot[0] = 0;}

/* V */
  
ydot[1] =  -y[1] * (((1-rUv) * foi) + omegav);

if( (y[1] < 0.0000000001) && (ydot[1] < 0)) {ydot[1] = 0;}


/* I_0 */
 
ydot[2] = y[0] * foi - (gamma + alpha*p) * y[2];

if( (y[2] < 0.0000000001) && (ydot[2] < 0)) {ydot[2] = 0;}


/* I_V */
  
ydot[3] = y[1] * (1-rUv) * foi - (gamma + (1-rLv)*alpha*p) * y[3];

if( (y[3] < 0.0000000001) && (ydot[3] < 0)) {ydot[3] = 0;}


/* I_C */

ydot[4] = y[8] * (1-rUc) * foi - (gamma + (1-rLc)*alpha*p) * y[4];

if( (y[4] < 0.0000000001) && (ydot[4] < 0)) {ydot[4] = 0;}


/* I_C_V */

ydot[5] = y[9] * (1-rUcv) * foi - (gamma + (1-rLcv)*alpha*p) * y[5];

if( (y[5] < 0.0000000001) && (ydot[5] < 0)) {ydot[5] = 0;}


/* Q */

ydot[6] = alpha * p * y[2] + (1-rLc) * alpha * p * y[4] - q * y[6];

if( (y[6] < 0.0000000001) && (ydot[6] < 0)) {ydot[6] = 0;}

/* Q_V */

ydot[7] = (1-rLv)  * alpha * p * y[3] + (1-rLcv) * alpha * p * y[5] - q * y[7];

if( (y[7] < 0.0000000001) && (ydot[7] < 0)) {ydot[7] = 0;}


/* C */
  
ydot[8] = (y[2] + y[4]) * gamma + q*y[6] - y[8] * (((1-rUc) * (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon)+ y[5]*betafunc(alpha,rUcv,rLcv,epsilon))) + omega);

if( (y[8] < 0.0000000001) && (ydot[8] < 0)) {ydot[8] = 0;}

/* C_V */

ydot[9] = (y[3] + y[5]) * gamma + q*y[7] - y[9] * (((1-rUcv) * (y[2]*betafunc(alpha,0,0,epsilon) + y[3]*betafunc(alpha,rUv,rLv,epsilon) + y[4]*betafunc(alpha,rUc,rLc,epsilon)  + y[5]*betafunc(alpha,rUcv,rLcv,epsilon))) + omegav);

if( (y[9] < 0.0000000001) && (ydot[9] < 0)) {ydot[9] = 0;}


/* output for Fmat */
  
yout[0] = y[0]*betafunc(alpha,0,0,epsilon);
yout[1] = y[0]*betafunc(alpha,rUv,rLv,epsilon);
yout[2] = y[0]*betafunc(alpha,rUc,rLc,epsilon);
yout[3] = y[0]*betafunc(alpha,rUcv,rLcv,epsilon);
yout[4] = 0;
yout[5] = 0;

yout[6] = y[1]*(1-rUv)*betafunc(alpha,0,0,epsilon);
yout[7] = y[1]*(1-rUv)*betafunc(alpha,rUv,rLv,epsilon);
yout[8] = y[1]*(1-rUv)*betafunc(alpha,rUc,rLc,epsilon);
yout[9] = y[1]*(1-rUv)*betafunc(alpha,rUcv,rLcv,epsilon);
yout[10] = 0;
yout[11] = 0;

yout[12] = y[8]*(1-rUc)*betafunc(alpha,0,0,epsilon);
yout[13] = y[8]*(1-rUc)*betafunc(alpha,rUv,rLv,epsilon);
yout[14] = y[8]*(1-rUc)*betafunc(alpha,rUc,rLc,epsilon);
yout[15] = y[8]*(1-rUc)*betafunc(alpha,rUcv,rLcv,epsilon);
yout[16] = 0;
yout[17] = 0;

yout[18] = y[9]*(1-rUcv)*betafunc(alpha,0,0,epsilon);
yout[19] = y[9]*(1-rUcv)*betafunc(alpha,rUv,rLv,epsilon);
yout[20] = y[9]*(1-rUcv)*betafunc(alpha,rUc,rLc,epsilon);
yout[21] = y[9]*(1-rUcv)*betafunc(alpha,rUcv,rLcv,epsilon);
yout[22] = 0;
yout[23] = 0;

yout[24] = 0;
yout[25] = 0;
yout[26] = 0;
yout[27] = 0;
yout[28] = 0;
yout[29] = 0;

yout[30] = 0;
yout[31] = 0;
yout[32] = 0;
yout[33] = 0;
yout[34] = 0;
yout[35] = 0;

  
 /* output for Vmat */
  
yout[36] = gamma + alpha*p;
yout[37] = 0;
yout[38] = 0;
yout[39] = 0;
yout[40] = 0;
yout[41] = 0;

yout[42] = 0;
yout[43] = gamma + alpha*p*(1-rLv);
yout[44] = 0;
yout[45] = 0;
yout[46] = 0;
yout[47] = 0;

yout[48] = 0;
yout[49] = 0;
yout[50] = gamma + alpha*p*(1-rLc);
yout[51] = 0;
yout[52] = 0;
yout[53] = 0;

yout[54] = 0;
yout[55] = 0;
yout[56] = 0;
yout[57] = gamma + alpha*p*(1-rLcv);
yout[58] = 0;
yout[59] = 0;

yout[60] = -1*alpha*p;
yout[61] = 0;
yout[62] = -1*alpha*p*(1-rLc);
yout[63] = 0;
yout[64] = q;
yout[65] = 0;

yout[66] = 0;
yout[67] = -1*alpha*p*(1-rLv);
yout[68] = 0;
yout[69] = -1*alpha*p*(1-rLcv);
yout[70] = 0;
yout[71] = q;
}

/* END file mymod.c */
