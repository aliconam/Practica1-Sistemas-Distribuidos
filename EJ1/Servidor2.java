import java.net.*;
import java.io.*;

public class Servidor2 {
    public static void main(String[] args) {
        try {
            // Crear socket servidor
            ServerSocket serverSocket = new ServerSocket(8888);
            System.out.println("Servidor iniciado. Esperando cliente...");

            // Esperar a que un cliente se conecte
            Socket clientSocket = serverSocket.accept();
            System.out.println("Cliente conectado desde " + clientSocket.getInetAddress().getHostName());

            // Crear stream de entrada para recibir mensajes del cliente
            InputStream inputStream = clientSocket.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

            // Crear stream de salida para enviar mensajes al cliente
            OutputStream outputStream = clientSocket.getOutputStream();
            PrintWriter printWriter = new PrintWriter(outputStream, true);

            // Leer y procesar mensajes del cliente
            String mensaje;
            do {
                mensaje = bufferedReader.readLine();
                System.out.println("Mensaje recibido: " + mensaje);

                // Responder al cliente con un mensaje personalizado
                String respuesta = "Hola que tal";
                printWriter.println(respuesta);
                System.out.println("Respuesta enviada: " + respuesta);
            } while (!mensaje.equals("FIN"));

            // Cerrar streams y socket
            bufferedReader.close();
            printWriter.close();
            clientSocket.close();
            serverSocket.close();
            System.out.println("Conexión cerrada.");
        } catch (IOException ex) {
            System.err.println("Error al iniciar el servidor: " + ex.getMessage());
        }
    }
}

