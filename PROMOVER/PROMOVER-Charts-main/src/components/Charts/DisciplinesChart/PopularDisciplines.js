import React from "react";
import Chart from "react-apexcharts";

const PopularDisciplines = (props) => {
  let popular_disciplines = [
    { name: "Desenho Técnico 1 - UFSM", total: 15 },
    { name: "Cálculo B - ABC", total: 14 },
    { name: "Empreendedorismo - DEF", total: 13 },
  ];

  let popular_disciplines_name = popular_disciplines.map((data) => data.name);
  let popular_disciplines_total = popular_disciplines.map((data) => data.total);

  let state = {
    series: popular_disciplines_total,
    options: {
      plotOptions: {
        pie: {
          donut: {
            labels: {
              show: true,
            },
          },
        },
      },
      theme: { palette: "palette6" },
      chart: {
        width: 350,
        type: "pie",
        toolbar: {
          show: true,
        },
      },
      labels: popular_disciplines_name,
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
        <h2>4.4 Turmas com maior solicitações</h2>
      </center>
      <Chart
        options={state.options}
        series={state.series}
        type="donut"
        height={350}
      />
    </div>
  );
};

export default PopularDisciplines;
