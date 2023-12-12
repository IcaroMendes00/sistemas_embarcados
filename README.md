# Projeto de Controle de Acesso IoT e Sistemas Embarcados

Este projeto visa criar um sistema de controle de acesso inteligente, integrando tecnologias como Bluetooth, RFID e MQTT para oferecer praticidade, segurança e conectividade. Utilizamos uma variedade de componentes, incluindo ESP32-S3, ESP01, NodeMCU, Módulo RFID-RC522, LEDs, protocolo MQTT, BeagleBone Element14 e Firebase como middleware.

## Componentes Principais

- 1x ESP32-S3
- 1x ESP01
- 1x NodeMCU
- 1x Módulo RFID-RC522
- 2x LEDs
- Protocolo MQTT
- BeagleBone Element14
- Firebase Middleware

## Introdução

Nos dias atuais, a Internet das Coisas (IoT) e os sistemas embarcados desempenham um papel fundamental na criação de soluções inteligentes para diversos setores. Este projeto visa integrar tecnologias avançadas para fornecer um sistema de controle de acesso robusto e eficiente, combinando a flexibilidade do Bluetooth, a segurança do RFID e a confiabilidade do MQTT.

## Objetivos

### Objetivo Principal

Desenvolver um sistema de controle de acesso que ofereça praticidade, segurança e conectividade. A utilização do ESP32 para controle via Bluetooth e módulo RFID para autenticação proporcionará múltiplas camadas de segurança, garantindo uma experiência de acesso fluida e confiável.

### Objetivos Específicos

1. **Controle de Acesso Via Bluetooth:**
   - Configurar o ESP32 para estabelecer conexões Bluetooth seguras.
   - Desenvolver algoritmos para autorização de dispositivos móveis por meio do Bluetooth.

2. **Integração de Autenticação RFID:**
   - Conectar e configurar um módulo RFID para autenticação adicional.
   - Desenvolver algoritmos de autenticação RFID para garantir acesso somente a usuários autorizados.

3. **Estabelecimento de Comunicação MQTT:**
   - Implementar o protocolo MQTT para facilitar a troca eficiente de mensagens entre dispositivos.
   - Assegurar a segurança da comunicação MQTT, utilizando criptografia, se necessário.

4. **Desenvolvimento do Middleware Firebase (BeagleBone Black):**
   - Configurar o BeagleBone Black como um gateway para gerenciar a comunicação entre dispositivos.
   - Implementar um middleware usando Firebase para processar, armazenar e recuperar dados de acesso de forma centralizada.

5. **Criação de Interface de Gerenciamento Remoto:**
   - Desenvolver uma interface web ou aplicativo para gerenciamento remoto do sistema.
   - Integrar a interface com o Firebase para exibir dados em tempo real e permitir a administração eficiente.

6. **Documentação Completa do Projeto:**
   - Criar documentação técnica detalhada, incluindo diagramas, fluxogramas.
   - Facilitar a compreensão do projeto por outros desenvolvedores e usuários finais.

## Funcionamento do Sistema

- **Controle de Acesso via Bluetooth:**
  - Os usuários autorizados podem utilizar seus dispositivos móveis para estabelecer uma conexão Bluetooth com o ESP32, permitindo a abertura da fechadura de forma segura.

- **Autenticação RFID:**
  - Para uma camada adicional de segurança, o sistema exigirá autenticação RFID, garantindo que apenas usuários autorizados possam acessar o ambiente.

- **Comunicação MQTT:**
  - A comunicação entre o ESP32, o BeagleBone Black e outros dispositivos será intermediada pelo protocolo MQTT. Isso garantirá uma troca de dados eficiente e em tempo real.

- **Firebase Middleware:**
  - O BeagleBone Black, como gateway, utilizará o Firebase como middleware para armazenar e processar informações de acesso. Isso possibilitará o monitoramento remoto e a gestão simplificada do sistema.


LINK DE APRESENTAÇÂO DO PROJETO: https://youtu.be/qC_HJmWepyM?si=lFAd0MzHrvhawCCK

