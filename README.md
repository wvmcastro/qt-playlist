# Desafio técnico Playlist Qt (Ton) #

Desafio técnico da TechTon para a vaga de Desenvolvedor C++ remoto. O desafio consiste em desenvolver um programa feito em Qt que possa criar e executar uma playlist do Spotify, utilizando a API pública do Spotify (https://developer.spotify.com/web-api/).

### O usuário deveria ser capaz de:**
- [x] Criar uma nova playlist (localmente)
- [x] Buscar uma música a partir de palavras chave
- [x] Adicionar/excluir música da playlist
- [ ] Executar a playlist (nesse caso tocando os samples do spotify)

Das funcionalidades exigidas acima, apenas a execução de músicas não está implementada. 

### Requisitos funcionais
- [x] Deve ser desenvolvido com Qt (em C++)
- [x] UI deve ser feita com QWidgets
- [x] A aplicação deve rodar pelo menos em Desktop (Linux, Windows ou Mac)
- [x] Os dados de usuários e suas playlists devem ser armazenados offline

## Como fazer o build do projeto
As únicas dependências do projeto são:
- Qt (utilizei o 6.2.1)
- cpprest (https://github.com/microsoft/cpprestsdk)

Além das dependências é necessário configurar o aquivo de configuração **config.h** dentro da pasta **include**. Para isso é preciso das chaves **client id** e **client secret**, obtidas no dashboard do desenvolvedor em https://developer.spotify.com/dashboard/, além das chaves, também é preciso do caminho absoluto do banco de dados SQLite, **appdatabase.sql** no disco. 
