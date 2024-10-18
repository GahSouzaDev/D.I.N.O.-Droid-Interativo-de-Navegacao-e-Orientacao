
# Nome do Droid: **D.I.N.O.**

### Droid Interativo de Navegação e Orientação

O **D.I.N.O.** é um robô guia inteligente, desenvolvido para auxiliar pessoas na locomoção em ambientes complexos, como aeroportos, shopping centers, museus e grandes edifícios. Seu design combina mobilidade autônoma com interação natural, fornecendo uma experiência amigável e intuitiva de navegação para usuários em busca de locais específicos.

## Funcionalidades

- **Navegação Autônoma:** O D.I.N.O. utiliza sensores de mapeamento e algoritmos avançados para traçar rotas em tempo real, guiando os usuários com precisão até destinos como banheiros, balcões de atendimento, portões de embarque, ou qualquer outro ponto de interesse.
- **Interação Intuitiva:** Responde a comandos de voz e perguntas simples, fornecendo informações diretas sobre direções ou serviços. A interação pode ser acompanhada por instruções visuais e sonoras para facilitar a orientação.
- **Assistência em Ambientes Complexos:** Ideal para locais com muitas pessoas ou sinalizações confusas, o D.I.N.O. garante que os usuários possam se deslocar com facilidade e confiança.
- **Design Amigável:** A aparência e o comportamento do robô foram projetados para evocar a robustez de um "dinossauro moderno", misturando simpatia com uma presença tecnológica segura.

## Objetivo

O objetivo do **D.I.N.O.** é melhorar a experiência de navegação em grandes espaços fechados, oferecendo uma solução de orientação acessível e fácil de usar. A ideia é proporcionar aos usuários uma experiência semelhante a ter um guia pessoal que pode ser abordado para pedir direções e que os acompanha até o destino desejado.

## Tecnologias Utilizadas

- **Sensores de Mapeamento e Navegação** (como LiDAR ou sensores ultrassônicos)
- **Algoritmos de Mapeamento e Localização** (SLAM - Simultaneous Localization and Mapping)
- **Placa de Controle:** ESP32 com controlador de servos
- **Reconhecimento de Voz:** Utiliza comandos de voz para receber instruções e fornecer respostas
- **Sistema de Locomoção Bípede:** Motores de servo para garantir movimentos suaves e naturais

## Instalação e Configuração

1. **Baixe o código-fonte:** Clone o repositório para o seu ambiente local.
2. **Configuração do hardware:** Monte o robô conforme as instruções no diretório de documentação.
3. **Instalação de bibliotecas:** Certifique-se de ter todas as bibliotecas necessárias instaladas, incluindo suporte para ESP32 e controladores de servos.
4. **Carregue o código no ESP32:** Utilize a IDE Arduino para compilar e carregar o firmware no microcontrolador.
5. **Calibração inicial:** Realize a calibração dos sensores e motores para garantir que o robô esteja operando corretamente.

## Uso

- **Iniciar o D.I.N.O.:** Ligue o robô e permita que ele faça a calibração inicial.
- **Comandos de voz:** Pergunte ao D.I.N.O. sobre a localização de um local específico e siga as instruções fornecidas para chegar ao destino.
- **Interação adicional:** O robô pode responder a perguntas básicas sobre os serviços disponíveis no ambiente e fornecer informações úteis.

## Contribuições

Contribuições são bem-vindas! Para sugerir melhorias, envie um pull request ou abra uma issue para discutir a mudança desejada.