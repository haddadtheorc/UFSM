import React, { useState } from "react";
import Chart from "react-apexcharts";
import Filter from "../../Filters/Filter";

const RequestsByIfe = (props) => {
  const [filteredIFE, setFilteredIFE] = useState("UFSM");

  const filterChangeHandler = (selectedIFE) => {
    setFilteredIFE(selectedIFE);
  };

  var ife = props.data.filter((data) => data.name === filteredIFE);
  let ife_data = [];
  ife_data.push(
    ife[0].requests_approved,
    ife[0].requests_reproved_requisites,
    ife[0].requests_reproved_schedule,
    ife[0].requests_reproved_vacancy
  );

  let state = {
    series: ife_data,
    theme: { palette: "palette6" },
    options: {
      chart: {
        width: 350,
        type: "pie",
        toolbar: {
          show: true,
        },
      },
      labels: [
        "Aprovadas",
        "Reprovadas - Pré-Requisito",
        "Reprovadas - Horário",
        "Reprovadas - Vagas",
      ],
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
        <h2>4.2 Solicitações {filteredIFE}</h2>
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
export default RequestsByIfe;
