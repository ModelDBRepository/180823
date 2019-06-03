/*
  Author: YAMAZAKI, Tadashi (NumericalBrain.Org)
 */

#include<stdio.h>
#include<stdlib.h>
#include "param.h"

/*
  dw/dt
*/

double f_dw(const int training, const int t, const double v, const double w)
{
  if (training){
    return (1.0/tau_learn)*(-w + w_0 - c_okr);
  }else{
    return (1.0/tau_recov)*(-w + w_0);
  }
}
double f_dw4(const int training, const int t, const double v, const double w)
{
  if (training && t < 5*day){
    return (1.0/tau_learn)*(-w + w_0 - c_okr);
  }else{
    return (1.0/tau_recov)*(-w + w_0);
  }
}
double f_dw_wulff(const int training, const int t, const double v, const double w)
{
  return f_dw(training, t, v, w);
}

/*
  dv/dt
*/

double f_dv(const int training, const int t, const double v, const double w)
{
  return (1.0/tau_v) * (-w + w_mli);
}
double f_dv_shutdown4(const int training, const int t, const double v, const double w)
{
  if (4*day + 1*hour <= t){
    return 0;
  }
  return f_dv(training, t, v, w);
}
double f_dv_shutdown_delay(const int delay_min, const int training, 
			   const int t, const double v, const double w)
{
  if (training){
    return f_dv(training, t, v, w);
  }else{
    if (1*day <= t && t%(1*day) < 1*hour + delay_min*min && t < 6*day){
      return f_dv(training, t, v, w);
    }else{
      return 0;
    }
  }
}
double f_dv_muscimol(const int training, const int t, const double v, const double w)
{
  return f_dv_shutdown_delay(0, training, t, v, w);
}
double f_dv_muscimol30(const int training, const int t, const double v, const double w)
{
  return f_dv_shutdown_delay(30, training, t, v, w);
}
double f_dv_muscimol60(const int training, const int t, const double v, const double w)
{
  return f_dv_shutdown_delay(60, training, t, v, w);
}
double f_dv_muscimol90(const int training, const int t, const double v, const double w)
{
  return f_dv_shutdown_delay(90, training, t, v, w);
}
double f_dv_muscimol120(const int training, const int t, const double v, const double w)
{
  return f_dv_shutdown_delay(120, training, t, v, w);
}

double f_dv_ltd(const int training, const int t, const double v, const double w)
{
  if (v - w + w_mli > 0){
    return (1.0/tau_v) * (-w + w_mli);
  }else{
    return 0.0;
  }
}
double f_dv_wulff(const int training, const int t, const double v, const double w)
{
  return (1.0/tau_v) * (-w);
}

/*
  OKR gain
*/

double f_okr(const int training, const int t, const double v, const double w)
{
  return g_okr * (v - w + w_mli);
}
double f_okr_shutdown4(const int training, const int t, const double v, const double w)
{
  if (4*day + 1*hour <= t){
    return g_okr * (v);
  }
  return f_okr(training, t, v, w);
}
double f_okr_shutdown_delay(const int delay_min, const int training, const int t, const double v, const double w)
{
  if (training){
    return f_okr(training, t, v, w);
  }else{
    if (1*day <= t && t%(1*day) < 1*hour + delay_min*min && t < 6*day){
      return f_okr(training, t, v, w);
    }else{
      return g_okr * (v);
    }
  }
}
double f_okr_muscimol(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(0, training, t, v, w);
}
double f_okr_muscimol30(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(30, training, t, v, w);
}
double f_okr_muscimol45(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(45, training, t, v, w);
}
double f_okr_muscimol60(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(60, training, t, v, w);
}
double f_okr_muscimol90(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(90, training, t, v, w);
}
double f_okr_muscimol120(const int training, const int t, const double v, const double w)
{
  return f_okr_shutdown_delay(120, training, t, v, w);
}
double f_okr_ltd(const int training, const int t, const double v, const double w)
{
  if (v - w + w_mli > 0){
    return f_okr(training, t, v, w);
  }else{
    return 0;
  }
}
double f_okr_wulff(const int training, const int t, const double v, const double w)
{
  return g_okr * (v - w) + 1;
}
