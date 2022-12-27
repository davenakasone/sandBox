import cmath
import math
import os
import sys

os.system("clear")

fa = 19.43
fb = 10.52

t2_p = [20.0, 30.0, 40.0, 50.0]
t2_q = [22.2, 16.1, 14.1, 13.3]
t2_f = []
bar = 0.0
for xx in range(0, 4) :
    t2_f.append((t2_p[xx] * t2_q[xx]) / (t2_p[xx] + t2_q[xx]))
    bar = bar + t2_f[xx]

bar = bar/4
sig = 0
for xx in range(0, 4) :
    sig = sig + (t2_f[xx] - bar)**2

sigg = cmath.sqrt((1/3) * sig)
alp = sigg/2
perr =  -1 * (bar-fb) / fb
print(f"mean= {bar}")
print(f"alpha= {alp}")
print(f"pdiff= {perr*100} %")

t3_qoo = 7.4
t3_p = 6.9
t3_q = 18.7
t3_fab_oo = t3_qoo
t3_fab_pq = (t3_p * t3_q) / (t3_p + t3_q)
t3_fab_avg = (t3_fab_oo + t3_fab_pq) / 2
t3_fab_theo = (fa * fb) / (fa + fb)
perr = (t3_fab_avg - t3_fab_theo) / t3_fab_theo
print(f"\nfab_p=oo   {t3_fab_oo} cm")
print(f"fab_pq = {t3_fab_pq} cm")
print(f"fab_avg = {t3_fab_avg} cm")
print(f"fab_theo = {t3_fab_theo} cm")
print(f"%diff = {-1*perr*100} %")

t4_qoo = 19.7
t4_p = 31.9
t4_q = 26.9
t4_fbc_oo = t4_qoo
t4_fbc_pq = (t4_p * t4_q) / (t4_p + t4_q)
t4_fbc_avg = (t4_fbc_oo + t4_fbc_pq) / 2
t4_fc = (t4_fbc_avg * fb) / (fb - t4_fbc_avg)
print(f"\nfbc_oo = {t4_fbc_oo} cm")
print(f"fbc_pq = {t4_fbc_pq} cm")
print(f"fbc_avg = {t4_fbc_avg} cm")
print(f"fc = {t4_fc} cm")

print("\n\n\t\t~ ~ ~ DONE ~ ~ ~\n\n")
sys.exit()