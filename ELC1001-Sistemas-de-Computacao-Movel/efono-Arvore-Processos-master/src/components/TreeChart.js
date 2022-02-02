import React from "react";
import Tree from "react-tree-graph";
import "./TreeChart.css";

let data = {
  name: "Colour",
  pathProps: {},
  textProps: { x: -25, y: 25 },
  children: [
    {
      name: "Black",
      pathProps: { className: "black" },
      textProps: { x: -25, y: 25 },
      children: [],
    },
    {
      name: "Blue",
      pathProps: { className: "blue" },
      textProps: { x: -25, y: 25 },
      color: "blue",
      children: [
        {
          name: "Aquamarine",
          textProps: { x: -25, y: 25 },
          color: "aquamarine",
          children: [],
        },
        {
          name: "Cyan",
          textProps: { x: -25, y: 25 },
          color: "cyan",
          children: [],
        },
        {
          name: "Navy",
          textProps: { x: -25, y: 25 },
          color: "navy",
          children: [],
        },
        {
          name: "Turquoise",
          textProps: { x: -25, y: 25 },
          color: "turquoise",
          children: [],
        },
      ],
    },
    {
      name: "Green",
      pathProps: { className: "green" },
      textProps: { x: -25, y: 25 },
      color: "green",
      children: [],
    },
    {
      name: "Purple",
      pathProps: { className: "purple" },
      textProps: { x: -25, y: 25 },
      color: "purple",
      children: [
        {
          name: "Indigo",
          textProps: { x: -25, y: 25 },
          color: "indigo",
          children: [],
        },
        {
          name: "Violet",
          textProps: { x: -25, y: 25 },
          color: "violet",
          children: [],
        },
      ],
    },
    {
      name: "Red",
      pathProps: { className: "red" },
      textProps: { x: -25, y: 25 },
      color: "red",
      children: [
        {
          name: "Crimson",
          textProps: { x: -25, y: 25 },
          color: "crimson",
          children: [],
        },
        {
          name: "Maroon",
          textProps: { x: -25, y: 25 },
          color: "maroon",
          children: [],
        },
        {
          name: "Scarlet",
          textProps: { x: -25, y: 25 },
          color: "scarlet",
          children: [],
        },
      ],
    },
    {
      name: "White",
      pathProps: { className: "grey" },
      textProps: { x: -25, y: 25 },
      color: "grey",
      children: [],
    },
    {
      name: "Yellow",
      pathProps: { className: "yellow" },
      textProps: { x: -25, y: 25 },
      color: "yellow",
      children: [],
    },
  ],
};

const handleClick = (event: any, node: any) => {
  console.log("handle click ", event);
  console.log("handle click node", node);
  alert(`${node} got clicked`);
};

const TreeChart = () => {
  return (
    <div>
      <center>
        <h1> ADICIONAR num onclick deve remover todos os seus "irmãos"</h1>
        <Tree
          data={data}
          nodeRadius={15}
          margins={{ top: 20, bottom: 10, left: 20, right: 200 }}
          gProps={{
            className: "node",
            onClick: handleClick,
          }}
          height={700}
          width={1000}
        />
      </center>
    </div>
  );
};

export default TreeChart;
