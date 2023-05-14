import java.util.Scanner;

public class TesteCursos {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);

        Curso[] cursos = new Curso[4];

        for(int i = 0; i < cursos.length; i++) {

            System.out.println("Entre com o nome do curso:");
            String nome = scanner.next();

            System.out.println("Digite a carga horaria");
            int CH = scanner.nextInt();

            System.out.println("digite a quantidade de periodos:");
            int periodos = scanner.nextInt();

            System.out.println("Digite a formacao do curso");
            String tipo = scanner.next();
            
            cursos[i] = new Curso(nome, CH, periodos, tipo);

        }

        for(Curso curso : cursos){
            curso.mostrarDados();
            System.out.println();
        }

    }
}