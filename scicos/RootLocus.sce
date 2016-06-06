function out = Quantizer(in_power)
    // input
    power = in_power(1);
    // Quantization
    Quanta = 1;
    power = round(power/Quanta)*Quanta;
    // Output
    out = power;
endfunction

//stacksize(99999999);
s = poly(0, 's');
Dt = 0.005; // 5 millisecondi
t = [0 : Dt : 3];
//Input function: step
u = ones(1,size(t,2));



// Parameters
k = 0.15;
xi = 0.88;
on = 7.90;


// limitation
OS = (25/100);
xil = -(log(OS)/sqrt(%pi^2+log(OS)^2));

TS = 0.4;
TSt = 5/100;
onxi = -(log(TSt)/TS);


//printf("onxi1 = %f, onxi2 = %f, onxi3 = %f\n", onl*xil, onxi, onxi2);

//Transfer function
G = k/((s^2/on^2) + 2*(xi/on)*s + 1);//2 poli //p= -2.665
G = syslin('c',G);
y = csim('step',t,G);


//Controller design

Kc = 37;
C = ((s+10)^2)/(s*(s+80));


//Closed loop step response
Gcl = (Kc*C*G)/(1+Kc*C*G);
Gcl = syslin('c', Gcl);
ycl = csim('step',t,Gcl);


scf(0);
clf;
plot(t,u, 'r'); // reference
plot(t,ycl,'g'); // closed loop response
plot(t,(1+OS),'r--');
plot(t,(1+TSt),'b--');
plot(t,(1-TSt),'b--');
// root locus
scf(1);
clf;
evans (C*G,Kc); 
sgrid(xil,onxi);





Cd=ss2tf(cls2dls(tf2ss(Kc*C),0.005)) 




