#include "rod_math_v9.h"

int main(){
    
    float m_im1[3] = {-8.78125100e-11, 1.16555800e-10, -8.71992700e-11};
    float e_im1[3] = {1.34365400e-08, 6.62241900e-09, -4.68984700e-09};
    float e_i[3] = {6.55867000e-09, 2.03361000e-09, 5.91157700e-09};
    float m_prime[3];
    rod::parallel_transport(m_im1, m_prime, e_im1, e_i);
    float dotprod = m_prime[rod::x]*e_i[rod::x]+m_prime[rod::y]*e_i[rod::y]+m_prime[rod::z]*e_i[rod::z];
    if (dotprod < 0.01){
        return 0;
    }
    else{
        return 1;
    }
}
