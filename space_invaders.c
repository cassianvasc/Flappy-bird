#include <stdlib.h>

#define true 1
#define false 0
#define LARGURA 1920
#define ALTURA 1080

typedef unsigned char bool;

// ==============================================
//  STRUCTS AUXILIARES
// ==============================================

typedef struct {
    float x;
    float y;
} vec2;

// ==============================================
//  STRUCTS PRINCIPAIS
// ==============================================

typedef struct {
    vec2 posicao;
    vec2 dimensao;  // Largura e altura
    int vida_restante;
} Player;

typedef struct Inimigo {
    vec2 posicao;
    vec2 dimensao;
    struct Inimigo* prox;
} Inimigo;

typedef struct Projetil {
    vec2 posicao;
    vec2 velocidade;
    vec2 dimensao;
    struct Projetil* prox;
} Projetil;

// ==============================================
//  LISTAS ENCADEADAS
// ==============================================

typedef struct {
    Inimigo* inicio;
    Inimigo* fim;
} InimigoList;

typedef struct {
    Projetil* inicio;
    Projetil* fim;
} ProjetilList;

// ==============================================
//  FUNÇÕES AUXILIARES DE VETOR
// ==============================================

vec2 _vec2(float x, float y) { return (vec2){x, y}; }
vec2 vec2_add(vec2 a, vec2 b) { return (vec2){a.x + b.x, a.y + b.y}; }

// ==============================================
//  CONSTRUTORES DE LISTAS
// ==============================================

InimigoList* new_InimigoList() { return calloc(1, sizeof(InimigoList)); }
ProjetilList* new_ProjetilList() { return calloc(1, sizeof(ProjetilList)); }

// ==============================================
//  PLAYER
// ==============================================

Player* new_Player(vec2 posicao, vec2 dimensao, int vida_inicial) {
    Player* p = malloc(sizeof(Player));
    p->posicao = posicao;
    p->dimensao = dimensao;
    p->vida_restante = vida_inicial;
    return p;
}

void Player_mover(Player* player, vec2 velocidade) {
    player->posicao = vec2_add(player->posicao, velocidade);
}

void Player_desenhar(Player* player) {
    // Função para ser implementada na parte gráfica
}

// ==============================================
//  INIMIGO
// ==============================================

Inimigo* new_Inimigo(vec2 posicao, vec2 dimensao, Inimigo* prox) {
    Inimigo* ini = malloc(sizeof(Inimigo));
    ini->posicao = posicao;
    ini->dimensao = dimensao;
    ini->prox = prox;
    return ini;
}

void Inimigo_mover(Inimigo* inimigo, vec2 velocidade) {
    inimigo->posicao = vec2_add(inimigo->posicao, velocidade);
}

void Inimigo_desenhar(Inimigo* inimigo) {
    // Função para ser implementada na parte gráfica
}

// ==============================================
//  PROJETIL
// ==============================================

Projetil* new_Projetil(vec2 posicao, vec2 velocidade, vec2 dimensao, Projetil* prox) {
    Projetil* proj = malloc(sizeof(Projetil));
    proj->posicao = posicao;
    proj->velocidade = velocidade;
    proj->dimensao = dimensao;
    proj->prox = prox;
    return proj;
}

void Projetil_atualizar(Projetil* proj) {
    proj->posicao = vec2_add(proj->posicao, proj->velocidade);
}

void Projetil_desenhar(Projetil* proj) {
    // Função para ser implementada na parte gráfica
}

// ==============================================
//  DETECÇÃO DE COLISÃO E LIMITE DE TELA
// ==============================================

bool Projetil_colidir_Inimigo(Projetil* proj, Inimigo* ini) {
    return (proj->posicao.x < ini->posicao.x + ini->dimensao.x &&
            proj->posicao.x + proj->dimensao.x > ini->posicao.x &&
            proj->posicao.y < ini->posicao.y + ini->dimensao.y &&
            proj->posicao.y + proj->dimensao.y > ini->posicao.y);
}

bool Projetil_colidir_Player(Projetil* proj, Player* player) {
    return (proj->posicao.x < player->posicao.x + player->dimensao.x &&
            proj->posicao.x + proj->dimensao.x > player->posicao.x &&
            proj->posicao.y < player->posicao.y + player->dimensao.y &&
            proj->posicao.y + proj->dimensao.y > player->posicao.y);
}

bool Projetil_foraDaTela(Projetil* proj) {
    return (proj->posicao.x + proj->dimensao.x < 0 ||
            proj->posicao.x > LARGURA ||
            proj->posicao.y + proj->dimensao.y < 0 ||
            proj->posicao.y > ALTURA);
}

// ==============================================
//  LISTA DE PROJETEIS — OPERAÇÕES BÁSICAS
// ==============================================

void ProjetilList_remover(ProjetilList* list, Projetil* atual, Projetil* anterior) {
    if (atual == list->inicio) list->inicio = atual->prox;
    if (atual == list->fim) list->fim = anterior;
    if (anterior != NULL) anterior->prox = atual->prox;
    free(atual);
}

void ProjetilList_limparForaDaTela(ProjetilList* list) {
    Projetil* atual = list->inicio;
    Projetil* anterior = NULL;

    while (atual != NULL) {
        if (Projetil_foraDaTela(atual)) {
            Projetil* temp = atual->prox;
            ProjetilList_remover(list, atual, anterior);
            atual = temp;
            continue;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void ProjetilList_atualizar(ProjetilList* list) {
    Projetil* atual = list->inicio;
    while (atual != NULL) {
        Projetil_atualizar(atual);
        atual = atual->prox;
    }
    ProjetilList_limparForaDaTela(list);
}

// ==============================================
//  LISTA DE PROJETEIS — COLISÕES
// ==============================================

void ProjetilList_colidirPlayer(ProjetilList* list, Player* player) {
    Projetil* atual = list->inicio;
    Projetil* anterior = NULL;

    while (atual != NULL) {
        if (Projetil_colidir_Player(atual, player)) {
            player->vida_restante--;
            Projetil* temp = atual->prox;
            ProjetilList_remover(list, atual, anterior);
            atual = temp;
            continue;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void ProjetilList_colidirInimigo(ProjetilList* pList, InimigoList* iList) {
    Projetil* projAnterior = NULL;
    Projetil* projAtual = pList->inicio;

    while (projAtual != NULL) {
        bool projRemovido = false;
        Inimigo* iniAnterior = NULL;
        Inimigo* iniAtual = iList->inicio;

        while (iniAtual != NULL) {
            if (Projetil_colidir_Inimigo(projAtual, iniAtual)) {
                if (iniAtual == iList->inicio) iList->inicio = iniAtual->prox;
                if (iniAtual == iList->fim) iList->fim = iniAnterior;
                if (iniAnterior != NULL) iniAnterior->prox = iniAtual->prox;
                free(iniAtual);

                Projetil* temp = projAtual->prox;
                ProjetilList_remover(pList, projAtual, projAnterior);
                projAtual = temp;
                projRemovido = true;
                break;
            }

            iniAnterior = iniAtual;
            iniAtual = iniAtual->prox;
        }

        if (!projRemovido) {
            projAnterior = projAtual;
            projAtual = projAtual->prox;
        }
    }
}

// ==============================================
//  ADIÇÃO DE PROJETEIS
// ==============================================

void ProjetilList_adicionarDoPlayer(ProjetilList* list, Player* player, vec2 velocidade, vec2 dimensao) {
    vec2 pos = _vec2(
        player->posicao.x + player->dimensao.x / 2 - dimensao.x / 2,
        player->posicao.y - dimensao.y
    );

    Projetil* novo = new_Projetil(pos, velocidade, dimensao, NULL);

    if (list->fim != NULL)
        list->fim->prox = novo;
    else
        list->inicio = novo;

    list->fim = novo;
}

void ProjetilList_adicionarDoInimigo(ProjetilList* list, Inimigo* inimigo, vec2 velocidade, vec2 dimensao) {
    vec2 pos = _vec2(
        inimigo->posicao.x + inimigo->dimensao.x / 2 - dimensao.x / 2,
        inimigo->posicao.y + inimigo->dimensao.y
    );

    Projetil* novo = new_Projetil(pos, velocidade, dimensao, NULL);

    if (list->fim != NULL)
        list->fim->prox = novo;
    else
        list->inicio = novo;

    list->fim = novo;
}

// ==============================================
//  INIMIGOLIST
// ==============================================

void InimigoList_atualizar(InimigoList* list, vec2 velocidade) {
    Inimigo* atual = list->inicio;
    while (atual != NULL) {
        Inimigo_mover(atual, velocidade);
        atual = atual->prox;
    }
}

// ==============================================
//  GAME LOOP SIMPLIFICADO
// ==============================================

void Game_update(Player* player, InimigoList* inimigos, ProjetilList* projeteisPlayer, ProjetilList* projeteisInimigo) {
    // Atualiza projeteis
    ProjetilList_atualizar(projeteisPlayer);
    ProjetilList_atualizar(projeteisInimigo);

    // Colisões
    ProjetilList_colidirInimigo(projeteisPlayer, inimigos);
    ProjetilList_colidirPlayer(projeteisInimigo, player);

    // Atualiza inimigos (exemplo: descem na tela)
    InimigoList_atualizar(inimigos, _vec2(0, 1));

    // Aqui poderia ter lógica para inimigos atirarem periodicamente
}
