function analysis(in)

step_value = in;
loadmatfile("-ascii", strcat(["F:\ScicosExercise\scicos\data_files_final\d",string(step_value),".dat"]));
data_name = strcat(["d",string(step_value)]);
data = eval(data_name);;
timestamp = data(:,1);
timestamp = timestamp - timestamp(1);
speed = data(:,2);
speed = speed - speed(1);
speedsize = size(speed,1);

alpha = 5;
q = speed($);
Ts = -1;
speed_at_Ts = -1;
// calcolo il sellting time
for i=speedsize:-1:1
    if (abs(q - speed(i))<(alpha/100*q)) then
          Ts = timestamp(i);
          speed_at_Ts = speed(i);
    else
          break;
    end    
end

overshoot = (max(speed)-step_value)/step_value;

scf(in);
//clf;
plot(timestamp,step_value*1.05, 'r--');
plot(timestamp,step_value*0.95, 'r--');
plot([Ts, Ts], [0, speed_at_Ts]);
plot(timestamp, step_value*1.2, 'b--');
plot(timestamp, speed,'r' );
plot(timestamp, step_value, 'y');



printf("speed= %d, ts= %f, ov= %f\n", step_value, Ts, overshoot);
endfunction



for i=2:1:12
    analysis(i);
end    
