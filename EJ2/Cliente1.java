import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Cliente1 {
    public static void main(String[] args) throws IOException {
        // Conectar con el servidor
        String host = "localhost";
        int puerto = 8888;
        Socket socket = new Socket(host, puerto);
        System.out.println("Conectado al servidor");

        // Crear flujos de entrada y salida
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // Leer números del usuario y enviarlos al servidor
        Scanner scanner = new Scanner(System.in);
        int num;
        do {
            num = scanner.nextInt();
            // Enviar número al servidor
            out.println(num);

            // Leer respuesta del servidor
            String response = in.readLine();
            System.out.println("Respuesta del servidor: " + num);
        } while (num != 0);

        // Cerrar conexión
        scanner.close();
        in.close();
        out.close();
        socket.close();
        System.out.println("Conexión cerrada");
    }
}


