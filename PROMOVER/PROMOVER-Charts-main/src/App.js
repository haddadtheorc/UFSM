import React from "react";
import Charts from "./components/Charts/Charts";
import "./App.css";
import data from "./data";

const App = () => {
  return (
    <div>
      <Charts data={data} />
    </div>
  );
};

export default App;
