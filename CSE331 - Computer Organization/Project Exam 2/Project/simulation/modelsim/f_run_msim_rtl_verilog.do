transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/SingleCycleMIPS.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/PcModule.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/ControlUnit.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/AluModule.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/RegisterFile.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/InstructionFetch.v}
vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/cemal_bolat {C:/Users/user/Desktop/cemal_bolat/DataMemory.v}

