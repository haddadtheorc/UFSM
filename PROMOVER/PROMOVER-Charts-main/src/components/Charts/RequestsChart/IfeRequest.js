import React from "react";
import Chart from "react-apexcharts";

const IfeRequest = (props) => {
  let ife_requests_total = props.data.map((data) => data.requests_total);
  let ife_name = props.data.map((data) => data.name);

  let state = {
    series: ife_requests_total,
    options: {
      theme: { palette: "palette8" },
      chart: {
        width: 350,
        type: "pie",
        toolbar: {
          show: true,
        },
      },
      labels: ife_name,
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
        <h2>2.1 Solicitações Recebidas</h2>
      </center>
      <Chart
        options={state.options}
        series={state.series}
        type="pie"
        height={350}
      />
    </div>
  );
};

export default IfeRequest;
