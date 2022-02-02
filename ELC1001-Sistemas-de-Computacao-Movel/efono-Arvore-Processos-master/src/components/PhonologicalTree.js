import React, { useState } from "react";
import "react-tree-graph/dist/style.css";
import text from "../data/data";
import "./tree_style.css";

//uma estrutura de árvore composta por nós que têm como atributo sua chave, nome, uma referencia ao seu nó pai, um array de referencias a seus nós filhos e um campo para declarar se é raiz
class TreeNode {
  constructor(key, name) {
    this.key = key;
    this.name = name;
    this.father = null;
    this.descendants = [];
    this.isRoot = false;
  }

  //uma função para, com um node alvo, seleciona cada filho dele e coloca a referencia de si mesmo no campo .father de cada filho
  declare_father() {
    this.descendants.map((descendant) => (descendant.father = this));
  }

  //uma função para, dado um nó, encontra seu pai e remove todos os seus filhos salvo o nó escolhido, para assim escolher o processo fonológico correto
  remove_siblings() {
    try {
      this.father.descendants = this.father.descendants.filter(
        (descendant) => descendant === this
      );
    } catch {}
  }
}

//uma função que dado um nó que não tem pai, o torna um nó raiz de sua árvore de processos fonológicos
function declareRoot(data) {
  data.forEach((data) => {
    if (data.father === null) {
      data.isRoot = true;
    }
  });
}

//uma função que dado um id de um node, devolve sua referência
function findNode(data, id) {
  for (var i in data) {
    if (data[i].key === id) {
      return data[i];
    }
  }
}

//o componente de processos fonológicos
const PhonologicalTree = (props) => {
  //criando um nó para cada objeto no data
  const data = text.map((entry) => new TreeNode(entry._id, entry.name));
  const [filteredData, setFilteredData] = useState(data);

  //comparando os nós criados com os nós no data, se ele tem filhos mapeio apenas seus nomes para o array de filhos
  data.forEach((data) => {
    text.forEach((entry) => {
      if (entry._id === data.key) {
        data.descendants = entry.children;
      }
    });
  });

  //aqui os nós tendo os nomes dos seus filhos, uso a findNode() para encontrar o nó correspondente e o adiciono no array de filhos
  data.forEach((node) => {
    let kids = [];
    try {
      node.descendants.forEach((coiso) => kids.push(findNode(data, coiso)));
      node.descendants = kids;
      kids = [];
    } catch {}
  });

  //percorrendo os nós para conectar os filhos aos pais
  data.forEach((node) => {
    try {
      node.declare_father();
    } catch {}
  });

  //o handler quando se clica em um processo fonológico
  //se procura o nó no qual foi clicado com a findNode()
  //remove seus irmãos com a .remove_siblings();
  //atualiza a data com a remoção dos irmãos usando a setFilteredData()
  //e atualiza o display da árvore na tela com o setFilteredPhonological(phonological_tree2)
  const handleClick = (event) => {
    findNode(filteredData, event.target.innerText).remove_siblings();
    setFilteredData(filteredData);
    setFilteredPhonological(phonological_tree2(filteredData));
  };

  //percorrendo o data e declarando os nós raízes para as árvores de processos
  declareRoot(data);

  //a árvore que será mostrada na tela
  const phonological_tree2 = (filteredData) => {
    let root_node = findNode(data, props.node);
    return (
      <ul>
        <li>
          <span>{root_node.key}</span>
          <ul>
            {root_node.descendants.map((kid) => {
              return (
                <li>
                  <span onClick={handleClick}>{kid.key}</span>
                </li>
              );
            })}
          </ul>
        </li>
      </ul>
    );
  };

  //o useState do html da árvore, para atualizar quando remover os irmãos
  const [filteredPhonological, setFilteredPhonological] = useState(
    phonological_tree2(filteredData)
  );

  //o retorno da árvore de processos em si
  return <div className="tree">{filteredPhonological}</div>;
};

export default PhonologicalTree;
