/*
  Author: YAMAZAKI, Tadashi (NumericalBrain.Org)
 */

#include<stdio.h>
#include<stdlib.h>
#include "param.h"

extern double f_dw(const int, const int, const double, const double);
extern double f_dw4(const int, const int, const double, const double);
extern double f_dw_wulff(const int, const int, const double, const double);

extern double f_dv(const int, const int, const double, const double);
extern double f_dv_shutdown4(const int, const int, const double, const double);
extern double f_dv_muscimol(const int, const int, const double, const double);
extern double f_dv_muscimol30(const int, const int, const double, const double);
extern double f_dv_muscimol60(const int, const int, const double, const double);
extern double f_dv_ltd(const int, const int, const double, const double);
extern double f_dv_wulff(const int, const int, const double, const double);

extern double f_okr(const int, const int, const double, const double);
extern double f_okr_shutdown4(const int, const int, const double, const double);
extern double f_okr_muscimol(const int, const int, const double, const double);
extern double f_okr_muscimol30(const int, const int, const double, const double);
extern double f_okr_muscimol60(const int, const int, const double, const double);
extern double f_okr_ltd(const int, const int, const double, const double);
extern double f_okr_wulff(const int, const int, const double, const double);

// Training paradigms
int training_5days(const int t)
{
  return (1*day <= t && t < 6*day && t%day < 1*hour) ? 1 : 0;
}
int training_8days(const int t)
{
  return (1*day <= t && t < 9*day && t%day < 1*hour) ? 1 : 0;
}
int training_mass(const int t)
{
  return (1*day <= t && t < 2*day && t%day < 1*hour) ? 1 : 0;
}
int training_space_15minsx4days(const int t)
{
  return (1*day <= t && t < 5*day && t%day < 15*min) ? 1 : 0;
}
int training_space_15minsx4hours(const int t)
{
  return ((1*day + 0*hour +  0*min <= t && t <= 1*day + 0*hour + 15*min) ||
	  (1*day + 1*hour + 15*min <= t && t <= 1*day + 1*hour + 30*min) ||
	  (1*day + 2*hour + 30*min <= t && t <= 1*day + 2*hour + 45*min) ||
	  (1*day + 3*hour + 45*min <= t && t <= 1*day + 3*hour + 60*min)) ? 1 : 0;
}
int training_space_15minsx2hours(const int t)
{
  return ((1*day +  0*min +  0*min <= t && t <= 1*day +  0*min + 15*min) ||
	  (1*day + 30*min + 15*min <= t && t <= 1*day + 30*min + 30*min) ||
	  (1*day + 60*min + 30*min <= t && t <= 1*day + 60*min + 45*min) ||
	  (1*day + 90*min + 45*min <= t && t <= 1*day + 90*min + 60*min)) ? 1 : 0;
}
int training_space_7_5minsx8days(const int t)
{
  return (1*day <= t && t < 9*day && t%day < 7.5*min) ? 1 : 0;
}

void transfer(const char *filename,
	      int (*training_pattern)(const int),
	      double (*f_dw)(const int, const int, const double, const double),
	      double (*f_dv)(const int, const int, const double, const double),
	      double (*f_okr)(const int, const int, const double, const double))
{
  double w = w_0, v = v_0;
  FILE *file;

  file = fopen(filename, "w");

  for(int t = 0; t < training_daymax; t += min){
    double okr, dw, dv;

    okr =(*f_okr)(training_pattern(t), t, v, w);
    dw = (*f_dw)(training_pattern(t), t, v, w);
    dv = (*f_dv)(training_pattern(t), t, v, w);
    fprintf(file, "%f %f %f %f\n", (double)t/day, okr, w, v);
    w += min*dw;
    if (w < 0){ w = 0; }
    v += min*dv;
    if (v < 0){ v = 0; }
  }

  fclose(file);
}

int main(void)
{
#if 1
  transfer("normal.dat", training_5days,
	   f_dw, f_dv, f_okr);
  transfer("normal4.dat", training_5days,
	   f_dw4, f_dv, f_okr);
  transfer("shutdown4.dat", training_5days,
	   f_dw, f_dv_shutdown4, f_okr_shutdown4);
  transfer("muscimol.dat", training_5days,
	   f_dw, f_dv_muscimol, f_okr_muscimol);
  transfer("muscimol30.dat", training_5days,
	   f_dw, f_dv_muscimol30, f_okr_muscimol30);
  transfer("muscimol60.dat", training_5days,
	   f_dw, f_dv_muscimol60, f_okr_muscimol60);

  transfer("mass.dat", training_mass,
           f_dw, f_dv, f_okr);
  transfer("space1.dat", training_space_15minsx4hours,
           f_dw, f_dv, f_okr);
  transfer("space2.dat", training_space_15minsx4days,
           f_dw, f_dv, f_okr);
  transfer("space3.dat", training_space_7_5minsx8days,
           f_dw, f_dv, f_okr);
#endif

#if 0
  // Set w_0=1.1, v_0=0.0 and c_okr=1.0.
  transfer("ltd.dat", training_8days,
	   f_dw, f_dv_ltd, f_okr_ltd);
#endif

#if 0
  // Set v_0 = 0.0.
  transfer("wulff.dat", training_8days,
	   f_dw_wulff, f_dv_wulff, f_okr_wulff);
#endif

  return 0;
}
