# Atividade-MD2

**Aluno:** Pedro Araujo Lucena
**Matrícula:** 222007077

---

## 2ª parte da questão 4

### 1. Resultado com valores fornecidos

A saída com os valores:
* **H:** 7
* **G:** 3
* **Zn:** 11
* **x:** 10
* **n1:** 13

**será 4**.

#### Demonstração:
Algoritmo de Euclides: 3 mod 11 = 3  
Algoritmo de Euclides: 11 mod 3 = 2  
Algoritmo de Euclides: 3 mod 2 = 1  
Algoritmo de Euclides: 2 mod 1 = 0  
&nbsp;  
Substituindo: o inverso de 3 em 11 eh 4.  
Realizando multiplicacao modular: 7 * 4 mod 11 = 6  
Observacao: 4 eh o inverso de 3 em 11.  
Resultado final da congruencia: 4

### 2. Resposta das Questões de V ou F:

( V ) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número. (Justificativa: Verdadeiro. O método encontra o inverso de a módulo n resolvendo a·x ≡ 1 (mod n).  
  
( F ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn. (Justificativa: Falso. O inverso modular não existe se o gcd ≠ 1.)  
  
( V ) A operação (H * inverso) % Zn representa a divisão modular de H por G. (Justificativa: Verdadeiro. Multiplicar por inverso modular equivale a dividir por G em Zn.)  
  
( F ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1. (Justificativa: Falso. O código não reduz o expoente via Teorema de Fermat; ele usa exponenciação modular direta.)  
  
( F ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização. (Justificativa: Falso. A implementação usa square-and-multiply, um método otimizado de exponenciação rápida.)  
  
( V ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0. (Justificativa: Verdadeiro. Faz x += m0 quando necessário para manter o resultado positivo.)  
  
( F ) O cálculo de φ(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo. (Justificativa: Falso. φ(n) é usada em qualquer caso; se n1 é primo, então φ(n1) = n1 − 1, logo a afirmação “apenas quando não é primo” é incorreta.)
