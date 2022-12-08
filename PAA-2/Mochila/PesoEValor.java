import java.math.BigDecimal;
import java.util.Arrays;
import java.util.List;

public class PesoEValor {
    
    private BigDecimal peso;
    
    private BigDecimal valor;
    
    private String descricao;
    
    public PesoEValor(final BigDecimal peso, final BigDecimal valor, final String descricao) {
        this.peso = peso;
        this.valor = valor;
        this.descricao = descricao;
    }
    
    public static List<PesoEValor> retornarListaComValores() {
        
        return Arrays.asList(
                new PesoEValor(BigDecimal.valueOf(1100D), BigDecimal.valueOf(1000D), "BlackWidow"),
                new PesoEValor(BigDecimal.valueOf(828D), BigDecimal.valueOf(989D), "Keychron K2"),
                new PesoEValor(BigDecimal.valueOf(1000D), BigDecimal.valueOf(637D), "Epomaker TH80"),
                new PesoEValor(BigDecimal.valueOf(1700D), BigDecimal.valueOf(1500D), "BlackWidow V3"),
                new PesoEValor(BigDecimal.valueOf(650D), BigDecimal.valueOf(495D), "Slyloong Sk64"),
                new PesoEValor(BigDecimal.valueOf(960D), BigDecimal.valueOf(386D), "Skyloong Gk75"),
                new PesoEValor(BigDecimal.valueOf(760D), BigDecimal.valueOf(553D), "Epomaker TH66"),
                new PesoEValor(BigDecimal.valueOf(1000D), BigDecimal.valueOf(259D), "Redragon Kumara"),
                new PesoEValor(BigDecimal.valueOf(650D), BigDecimal.valueOf(325D), "Skyloong GK64"),
                new PesoEValor(BigDecimal.valueOf(950D), BigDecimal.valueOf(499D), "Akko 3061S"));
        
    }
    
    public BigDecimal getPeso() {
        return this.peso;
    }
    
    public void setPeso(final BigDecimal peso) {
        this.peso = peso;
    }
    
    public BigDecimal getValor() {
        return this.valor;
    }
    
    public void setValor(final BigDecimal valor) {
        this.valor = valor;
    }
    
    public String getDescricao() {
        return this.descricao;
    }
    
    public void setDescricao(final String descricao) {
        this.descricao = descricao;
    }
    
}
