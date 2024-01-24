# findpeaks

![image](https://github.com/kybuivan/findpeaks/assets/68890407/ad7004c9-2612-466b-b493-c18fee8050bf)

- run code on [godbolt](https://godbolt.org/z/Kb8cfT8r3)
- using c++14
  
```bash
input = {2, 1, 1, 2, 3, 4, 5, 6, 0, 2, 3, 1, 4, 5, 1};

Program stdout
=========================================================
GetSignalInfoFunc
=========================================================

Signal (i: 0, v: 2, p: 1, t: Peak)
Signal (i: 1, v: 1, p: -1, t: Valley)
Signal (i: 2, v: 1, p: -1, t: Valley)
Signal (i: 3, v: 2, p: 0, t: None)
Signal (i: 4, v: 3, p: 0, t: None)
Signal (i: 5, v: 4, p: 0, t: None)
Signal (i: 6, v: 5, p: 0, t: None)
Signal (i: 7, v: 6, p: 7, t: Peak)
Signal (i: 8, v: 0, p: -8, t: Valley)
Signal (i: 9, v: 2, p: 1, t: None)
Signal (i: 10, v: 3, p: 3, t: Peak)
Signal (i: 11, v: 1, p: -5, t: Valley)
Signal (i: 12, v: 4, p: 2, t: None)
Signal (i: 13, v: 5, p: 5, t: Peak)
Signal (i: 14, v: 1, p: -4, t: Valley)
=========================================================

=========================================================
ouput
Signal (i: 0, v: 2, p: 1, t: Peak)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 4, v: 3, p: 0, t: None)
Signal (i: 1, v: 1, p: -1, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 8, v: 0, p: -5, t: Valley)
Signal (i: 2, v: 1, p: -1, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 8, v: 0, p: -5, t: Valley)
Signal (i: 3, v: 2, p: 0, t: None)
Signal (i: 4, v: 3, p: 0, t: None)
Signal (i: 5, v: 4, p: 0, t: None)
Signal (i: 6, v: 5, p: 0, t: None)
Signal (i: 7, v: 6, p: 5, t: Peak)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 8, v: 0, p: -5, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 9, v: 2, p: 1, t: None)
Signal (i: 10, v: 3, p: 2, t: Peak)
    Signal leftRef (i: 7, v: 6, p: 5, t: Peak)
    Signal rightRef (i: 12, v: 4, p: 2, t: None)
Signal (i: 11, v: 1, p: -2, t: Valley)
    Signal leftRef (i: 8, v: 0, p: -5, t: Valley)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 12, v: 4, p: 2, t: None)
Signal (i: 13, v: 5, p: 4, t: Peak)
    Signal leftRef (i: 7, v: 6, p: 5, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 14, v: 1, p: 1, t: Valley)
    Signal leftRef (i: 8, v: 0, p: -5, t: Valley)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
=========================================================

=========================================================
listPeaks
Signal (i: 0, v: 2, p: 1, t: Peak)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 4, v: 3, p: 0, t: None)
Signal (i: 7, v: 6, p: 5, t: Peak)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 10, v: 3, p: 2, t: Peak)
    Signal leftRef (i: 7, v: 6, p: 5, t: Peak)
    Signal rightRef (i: 12, v: 4, p: 2, t: None)
Signal (i: 13, v: 5, p: 4, t: Peak)
    Signal leftRef (i: 7, v: 6, p: 5, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
=========================================================

=========================================================
listValleys
Signal (i: 1, v: 1, p: -1, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 8, v: 0, p: -5, t: Valley)
Signal (i: 2, v: 1, p: -1, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 8, v: 0, p: -5, t: Valley)
Signal (i: 8, v: 0, p: -5, t: Valley)
    Signal leftRef (i: 0, v: 2, p: 1, t: Peak)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 11, v: 1, p: -2, t: Valley)
    Signal leftRef (i: 8, v: 0, p: -5, t: Valley)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
Signal (i: 14, v: 1, p: 1, t: Valley)
    Signal leftRef (i: 8, v: 0, p: -5, t: Valley)
    Signal rightRef (i: 14, v: 1, p: 1, t: Valley)
=========================================================
```
## See Also
[prominence](https://www.mathworks.com/help/signal/ug/prominence.html)
