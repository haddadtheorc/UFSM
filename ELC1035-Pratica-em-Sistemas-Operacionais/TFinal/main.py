import discord
import urllib.request
from bs4 import BeautifulSoup


# engloba as informações necessárias para buscar uma carta
class Card:
    def __init__(self, name):
        self.name = name
        self.color = False
        self.price = False
        self.format = False
        self.type = False


def treat_card_message(card_message):
    card_message = card_message.replace("!card ", "")
    card_message = card_message.replace(": ", ":")
    card_message = card_message.split(":")
    return card_message


# atribui o nome da carta à carta
def fill_card_info(card_name):
    card = Card(card_name)
    return card


# preenche os demais parâmetros adicionais de busca na carta
def fill_additional_card_info(card, card_info):
    card_info.pop(0)
    card_info = str(card_info)

    if("color" in card_info):
        card.color = True
    if("price" in card_info):
        card.price = True
    if("format" in card_info):
        card.format = True
    if("type" in card_info):
        card.type = True

    return card


# verifica se é uma busca básica/padrão (somente menor preço)
def is_basic_search(card):
    if(card.color == False and card.format == False and card.type == False and card.price == True):
        return True
    else:
        return False


# executa uma busca básica/padrão
def do_basic_search(soup):
    card_price = soup.find("div", {"class": "col-xl-6 col-6 b preco-menor"})
    card_price = card_price.text.strip()
    return str(card_price)


# executa uma busca com os parâmetros inseridos
def do_complex_search(card, soup):

    complex_search_return = ""

    if(card.price):
        card_price = soup.find(
            "div", {"class": "col-xl-6 col-6 b preco-menor"})
        card_price = card_price.text.strip()
        complex_search_return += ("\nPreço: " + card_price)

    if(card.color):
        card_color = soup.find(
            "div", {"class": "col-lg-6"})
        card_color = card_color.text.strip()
        complex_search_return += ("\n" + card_color)

    if(card.format):
        card_format = soup.find("div", {"class": "col-lg-12 col-lg-crop"})
        card_format = card_format.text.strip()
        complex_search_return += ("\n" + card_format)

    if(card.type):
        card_type = soup.find("div", {"class": "col-lg-6 html-typecard"})
        card_type = card_type.text.strip()
        complex_search_return += ("\n" + card_type)


    print(complex_search_return)
    return complex_search_return


# executa a busca da carta
def search_in_website(card):
    url = "https://www.ligamagic.com.br/" + \
        "?view=cards%2Fcard&card=" + card.name + "&tipo=1"
    url = url.replace(" ", "%20")
    url_contents = urllib.request.urlopen(url).read()
    soup = BeautifulSoup(url_contents, "html")

    if is_basic_search(card):
        basic_search = do_basic_search(soup)
        basic_search = "**" + card.name + "**, no menor da liga: " + basic_search
        return basic_search

    else:
        complex_search = do_complex_search(card, soup)
        return complex_search


# funcao principal de busca da carta
def search_card(message):

    # tratando a mensagem recebida
    card_info = treat_card_message((message.content.format(message)))

    # em caso de mensagem de ajuda
    if(card_info[0] == "help"):
        return "Para buscar uma carta, envie uma mensagem no padrão: **!card Nome_da_Carta: infos, desejadas**. \nAs informações adicionais são: *price, format, color, type*. \nCaso nenhuma informação adicional seja enviada, por padrão será buscado o menor preço da carta."

    # preenchendo a carta com seu nome
    card = fill_card_info(card_info[0])

    # caso hajam informaçoes adicionais a serem buscadas
    if len(card_info) > 1:
        card = fill_additional_card_info(card, card_info)
    else:
        card.price = True

    # realiza a busca
    search_return = search_in_website(card)
    return search_return


client = discord.Client()


@client.event
async def on_ready():
    print("BOT ONLINE")


@client.event
async def on_message(message):
    if(message.author == client):
        return
    if(message.content.startswith('!card ')):
        try:
            search_return = search_card(message)
            await message.channel.send(search_return)
        except:
            await message.channel.send("**ERRO** \nPara buscar uma carta, envie uma mensagem no padrão: **!cardy Nome_da_Carta: infos, desejadas**.")    

client.run()