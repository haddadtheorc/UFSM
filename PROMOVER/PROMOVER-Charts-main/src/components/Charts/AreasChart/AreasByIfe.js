import React, { useState } from "react";
import Chart from "react-apexcharts";
import Filter from "../../Filters/Filter";

const AreasByIfe = (props) => {
  const [filteredIFE, setFilteredIFE] = useState("UFSM");

  const filterChangeHandler = (selectedIFE) => {
    setFilteredIFE(selectedIFE);
  };

  var ife = props.data.filter((data) => data.name === filteredIFE);
  let ife_disciplines = ife.map((ife) => ife.disciplines);
  ife_disciplines = ife_disciplines[0];
  let ife_disciplines_total = ife_disciplines.map(
    (ife_disciplines) => ife_disciplines.value
  );

  let state = {
    series: ife_disciplines_total,
    options: {
      theme: { palette: "palette2" },
      chart: {
        width: 350,
        type: "pie",
        toolbar: {
          show: true,
        },
      },
      labels: ["Engenharias", "Biológicas", "Saúde"],
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
    <div id="chart">
      <center>
        <h2>2.3 Areas de conhecimento {filteredIFE}</h2>
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

export default AreasByIfe;
