import java.math.BigDecimal;
import java.util.List;

public class Pai {
    
    private BigDecimal fitness;
    
    private List<Integer> individuo;
    
    public Pai(final BigDecimal fitness, final List<Integer> individuo) {
        this.fitness = fitness;
        this.individuo = individuo;
    }
    
    public BigDecimal getFitness() {
        return this.fitness;
    }
    
    public void setFitness(final BigDecimal fitness) {
        this.fitness = fitness;
    }
    
    public List<Integer> getIndividuo() {
        return this.individuo;
    }
    
    public void setIndividuo(final List<Integer> individuo) {
        this.individuo = individuo;
    }
    
}
