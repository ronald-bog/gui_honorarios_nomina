#include <vcl.h>
#pragma hdrstop
#include <chrono>  // Para medir el tiempo

#include "Unit1.h"
#include "utils.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    // Deshabilitar el botón para evitar múltiples clics
    Button1->Enabled = false;

    // Reiniciar el Label del tiempo
    LabelTime->Caption = "0 segundos";

    // Mostrar "Iniciando Proceso" en el Label de estado
    LabelStatus->Caption = "Iniciando Proceso...";
    Application->ProcessMessages(); // Actualizar la interfaz gráfica

    // Iniciar el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    // Reiniciar la barra de progreso y el porcentaje
    ProgressBar1->Position = 0;
    LabelPercentage->Caption = "0%";
    Application->ProcessMessages();

    // Ejecutar las funciones y actualizar la barra de progreso y el porcentaje
    exe1();
    ProgressBar1->Position = 1;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe2();
    ProgressBar1->Position = 2;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe3();
    ProgressBar1->Position = 3;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe4();
    ProgressBar1->Position = 4;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe5();
    ProgressBar1->Position = 5;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe6();
    ProgressBar1->Position = 6;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe7();
    ProgressBar1->Position = 7;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    exe8();
    ProgressBar1->Position = 8;
    LabelPercentage->Caption = IntToStr((ProgressBar1->Position * 100) / ProgressBar1->Max) + "%";
    Application->ProcessMessages();

    // Detener el temporizador
    auto end = std::chrono::high_resolution_clock::now();

	// Calcular el tiempo transcurrido en segundos con milisegundos
	std::chrono::duration<double> elapsed = end - start;
	double elapsedSeconds = elapsed.count();

	// Mostrar el tiempo en el Label
	LabelTime->Caption = String(FormatFloat("0.000", elapsedSeconds)) + " segundos";

    // Mostrar "Proceso finalizado" en el Label de estado
    LabelStatus->Caption = "Proceso finalizado";

    // Habilitar el botón nuevamente
	Button1->Enabled = true;
}
//---------------------------------------------------------------------------




