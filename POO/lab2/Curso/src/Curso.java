public class Curso {
    String nome;
    int CH;
    int periodos;
    String tipo;
    
    public Curso(String nome, int CH, int periodos, String tipo) {
        this.nome = nome;
        this.CH = CH;
        this.periodos = periodos;
        this.tipo = tipo;
    }

    public void mostrarDados(){
        System.out.println("Nome: " + nome);
        System.out.println("CH: " + CH);
        System.out.println("periodos: " + periodos);
        System.out.println("formacao: " + tipo);

    }
}
