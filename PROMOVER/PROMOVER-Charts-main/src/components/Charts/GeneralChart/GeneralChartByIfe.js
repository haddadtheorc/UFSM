import React, { useState } from "react";
import Chart from "react-apexcharts";
import Filter from "../../Filters/Filter";

const GeneralChartByIfe = (props) => {
  const [filteredIFE, setFilteredIFE] = useState("UFSM");

  const filterChangeHandler = (selectedIFE) => {
    setFilteredIFE(selectedIFE);
  };

  var ife = props.data.filter((data) => data.name === filteredIFE);
  let ife_data = [];
  ife_data.push(ife[0].approved, ife[0].reproved, ife[0].dropouts);

  let state = {
    series: ife_data,
    options: {
      colors: ["#1a98ed", "#fa2f5a", "#6e7075"],
      chart: {
        width: 350,
        type: "pie",
        toolbar: {
          show: true,
        },
      },
      labels: ["Aprovações", "Reprovações", "Desistências"],
      responsive: [
        {
          breakpoint: 480,
          options: {
            chart: {
              width: 200,
            },
            legend: {
              position: "bottom",
            },
          },
        },
      ],
    },
  };

  return (
    <div>
      <center>
        <h2>1.2 Vagas Preenchidas {filteredIFE}</h2>
      </center>
      <div>
        <Filter
          selected={filteredIFE}
          data={props.data}
          onChangeFilter={filterChangeHandler}
        />
      </div>
      <div>
        <Chart
          options={state.options}
          series={state.series}
          type="pie"
          height={350}
        />
      </div>
    </div>
  );
};

export default GeneralChartByIfe;
