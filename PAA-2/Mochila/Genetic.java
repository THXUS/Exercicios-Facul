import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Genetic {
    
    public static final Double CHANCE_DE_MUTACAO = 0.05D;
    
    public static List<Integer> retornarIndividuo(final Integer numeroDeItens) {
        
        return IntStream.range(0, numeroDeItens).map(x -> ThreadLocalRandom.current().nextInt(2))
                .boxed()
                .collect(Collectors.toList());
        
    }
    
    public static List<List<Integer>> retornarPopulacao(final Integer numeroDeCromossomos, final Integer numeroDeItens) {
        return IntStream.range(0, numeroDeCromossomos).mapToObj(x -> Genetic.retornarIndividuo(numeroDeItens))
                .collect(Collectors.toList());
    }
    
    public static BigDecimal fitness(final List<Integer> individuo, final BigDecimal pesoMaximo, final List<PesoEValor> pesosEValores) {
        
        BigDecimal pesoTotal = BigDecimal.ZERO;
        BigDecimal valorTotal = BigDecimal.ZERO;
        
        int indice = 0;
        
        for (final Integer x : individuo) {
            pesoTotal = pesoTotal.add(pesosEValores.get(indice).getPeso().multiply(BigDecimal.valueOf((double) x)));
            valorTotal = valorTotal.add(pesosEValores.get(indice).getValor().multiply(BigDecimal.valueOf((double) x)));
            indice++;
        }
        
        return pesoMaximo.subtract(pesoTotal).compareTo(BigDecimal.ZERO) < 0 ? BigDecimal.ONE.negate() : valorTotal;
        
    }
    
    public static BigDecimal mediaFitness(final List<List<Integer>> populacao, final BigDecimal pesoMaximo, final List<PesoEValor> pesosEValores) {
        
        final BigDecimal somado = populacao.stream().filter(x -> Genetic.fitness(x, pesoMaximo, pesosEValores).compareTo(BigDecimal.ZERO) >= 0)
                .map(x -> Genetic.fitness(x, pesoMaximo, pesosEValores)).reduce(BigDecimal.ZERO, BigDecimal::add);
        
        return somado.divide(BigDecimal.valueOf(populacao.size()).multiply(BigDecimal.ONE), RoundingMode.HALF_UP);
        
    }
    
    public static List<List<Integer>> roleta(final List<Pai> pais) {
        
        final BigDecimal fitnessTotal = pais.stream().map(Pai::getFitness)
                .reduce(BigDecimal.ZERO, BigDecimal::add);
        
        final Integer indicePai = Genetic.sortear(fitnessTotal, null, pais);
        final Integer indiceMae = Genetic.sortear(fitnessTotal, indicePai, pais);
        
        return Arrays.asList(pais.get(indicePai).getIndividuo(), pais.get(indiceMae).getIndividuo());
        
    }
    
    public static int sortear(BigDecimal fitnessTotal, final Integer indiceAIgnorar, final List<Pai> valores) {
        final List<BigDecimal> roleta = new ArrayList<>();
        
        BigDecimal acumulado = BigDecimal.ZERO;
        
        final BigDecimal valorSorteado = BigDecimal.valueOf(ThreadLocalRandom.current().nextInt());
        
        if (indiceAIgnorar != null) {
            fitnessTotal = fitnessTotal.subtract(valores.get(indiceAIgnorar).getFitness());
        }
        
        for (int i = 0; i < valores.size(); i++) {
            if (Objects.nonNull(indiceAIgnorar) && indiceAIgnorar == i) {
                continue;
            }
            
            acumulado = acumulado.add(valores.get(i).getFitness());
            roleta.add(acumulado.divide(fitnessTotal, RoundingMode.HALF_UP));
            if (roleta.get(roleta.size() - 1).compareTo(valorSorteado) >= 0) {
                return i;
            }
            
        }
        return 0;
        
    }
    
    public static List<List<Integer>> evolve(final List<List<Integer>> populacao, final BigDecimal pesoMaximo, final List<PesoEValor> pesosEValores, final Integer numeroDeCromossomos) {
        
        final List<Pai> pais = populacao.stream().filter(x -> Genetic.fitness(x, pesoMaximo, pesosEValores).compareTo(BigDecimal.ZERO) >= 0)
                .map(x -> new Pai(Genetic.fitness(x, pesoMaximo, pesosEValores), x)).sorted(Comparator.comparing(Pai::getFitness, Comparator.reverseOrder()))
                .collect(Collectors.toList());
        
        final List<List<Integer>> filhos = new ArrayList<>();
        
        while (filhos.size() < numeroDeCromossomos) {
            
            final List<List<Integer>> homemEMulher = Genetic.roleta(pais);
            
            final int meio = (int) Math.ceil((double) homemEMulher.get(0).size() / 2);
            
            final List<Integer> filho = new ArrayList<>();
            
            filho.addAll(homemEMulher.get(0).subList(0, meio));
            filho.addAll(homemEMulher.get(1).subList(meio, homemEMulher.get(1).size()));
            
            filhos.add(filho);
            
        }
        
        for (final List<Integer> individuo : filhos) {
            if (CHANCE_DE_MUTACAO > ThreadLocalRandom.current().nextDouble()) {
                final int posicaoParaMutacao = ThreadLocalRandom.current().nextInt(individuo.size());
                if (individuo.get(posicaoParaMutacao).equals(1)) {
                    individuo.set(posicaoParaMutacao, 0);
                } else {
                    individuo.set(posicaoParaMutacao, 1);
                    
                }
            }
        }
        
        return filhos;
        
    }
    
    public static void main(final String[] args) {
        
        final List<PesoEValor> pesosEValores = PesoEValor.retornarListaComValores();
        
        final BigDecimal pesoMaximo = BigDecimal.valueOf(7000);
        
        final Integer numeroDeCromossomos = 400;
        
        final Integer geracoes = 300;
        
        final Integer numeroDeitens = pesosEValores.size();
        
        List<List<Integer>> populacao = Genetic.retornarPopulacao(numeroDeCromossomos, numeroDeitens);
        
        final List<BigDecimal> historicoDeFitness = new ArrayList<>();
        historicoDeFitness.add(Genetic.mediaFitness(populacao, pesoMaximo, pesosEValores));
        
        for (int i = 0; i < geracoes; i++) {
            
            populacao = Genetic.evolve(populacao, pesoMaximo, pesosEValores, numeroDeCromossomos);
            historicoDeFitness.add(Genetic.mediaFitness(populacao, pesoMaximo, pesosEValores));
        }
        
        final List<Integer> itensSelecionados = new ArrayList<>();
        
        Integer i = 0;
        
        for (final Integer individuo : populacao.get(populacao.size() - 1)) {
            
            if (individuo.equals(1)) {
                
                itensSelecionados.add(i);
            }
            
            i++;
            
        }
        
        BigDecimal valorTotal = BigDecimal.ZERO;
        for (final Integer indice : itensSelecionados) {
            System.out.println(pesosEValores.get(indice).getDescricao() + " " + "Valor R$" + pesosEValores.get(indice).getValor().toString());
            valorTotal = valorTotal.add(pesosEValores.get(indice).getValor());
            
        }
        
        System.out.println("Lucro Total: " + "R$" + valorTotal);
        
    }
    
}
