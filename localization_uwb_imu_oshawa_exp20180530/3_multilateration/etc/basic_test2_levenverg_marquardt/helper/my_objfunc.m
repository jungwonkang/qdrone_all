% 2018/8/25
% °­Á¤¿ø

function set_err = my_objfunc(params)

global r100 x100 y100 z100
global r101 x101 y101 z101
global r102 x102 y102 z102
global r103 x103 y103 z103
global z_fc


x_drone = params(1);
y_drone = params(2);
z_drone = params(3);

e_uwb100 = r100 - sqrt( (x_drone - x100)^2 + (y_drone - y100)^2 + (z_drone - z100)^2 );
e_uwb101 = r101 - sqrt( (x_drone - x101)^2 + (y_drone - y101)^2 + (z_drone - z101)^2 );
e_uwb102 = r102 - sqrt( (x_drone - x102)^2 + (y_drone - y102)^2 + (z_drone - z102)^2 );
e_uwb103 = r103 - sqrt( (x_drone - x103)^2 + (y_drone - y103)^2 + (z_drone - z103)^2 );
e_z      = z_drone - z_fc;

set_err = [e_uwb100; e_uwb101; e_uwb102; e_uwb103; e_z];

end