################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.c"
OBJ_FILES += "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.o"
"Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.o" : "..\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.c" "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.opt"

"Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.opt" : .refresh
	@argfile "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.opt" -o "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.o" "..\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.c" -Ctc26x --lsl-core=vtc -t -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo" -Wa-H"sfr/regtc26x.def" -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\CODE" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_Build" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_Impl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\_PinMap" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Asc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Lin" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Spi" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Icu" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Timer" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Cam" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\CStart" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Irq" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Trap" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Dma" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Dts" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Eray" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Crc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Fft" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Trig" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Hssl" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\I2c" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Driver" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Msc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Can" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Port" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Io" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Psi5" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Sent" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Src" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Src\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Timer" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Adc" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Std" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Platform" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Platform\Tricore" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Platform\Tricore\Compilers" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Sfr" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Sfr\TC26B" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Infra\Sfr\TC26B\_Reg" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Service" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\BaseSw\Service\CpuGeneric" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\seekfree_libraries" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\seekfree_libraries\common" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\Libraries\seekfree_peripheral" -I"D:\test\example\MT9V03x_1.8TFT_Mono_Demo\USER" --iso=99 --language=-gcc,-volatile,+strings,-kanji --fp-model=3 --switch=auto --align=0 --default-near-size=0 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=0 -g --error-limit=42 --source -c --dep-file="Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.d" -Wc--make-target="Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.o"
DEPENDENCY_FILES += "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.d"


GENERATED_FILES += "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.o" "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.opt" "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\.IfxCcu6_TimerWithTrigger.o.d" "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.src" "Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger\IfxCcu6_TimerWithTrigger.lst"
